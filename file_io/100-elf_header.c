/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100-elf_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <your_login>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:00:00 by <your_login>      #+#    #+#             */
/*   Updated: 2025/09/03 00:00:00 by <your_login>     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Program: elf_header
 * Usage:   elf_header elf_filename
 *
 * Displays: Magic, Class, Data, Version, OS/ABI, ABI Version, Type,
 *           Entry point address
 * Format: like `readelf -h` (GNU binutils 2.26.1) for those fields.
 *
 * Constraints:
 *   - Ubuntu 20.04, gcc, -std=gnu89, -Wall -Werror -Wextra -pedantic
 *   - No globals
 *   - read() at most twice (we use it once)
 *   - lseek() at most once (we use none)
 *   - printf allowed; errors -> stderr; exit(98) on error/non-ELF
 */

#include <stdio.h>      /* printf */
#include <unistd.h>     /* read, write, close */
#include <fcntl.h>      /* open */
#include <stdlib.h>     /* exit */
#include <elf.h>        /* Elf32_Ehdr, Elf64_Ehdr, EI_* */
#include <sys/types.h>  /* ssize_t */
#include <sys/stat.h>   /* open */
#include <stdint.h>     /* uint*_t */

/* ---------- Internal helpers (no globals) -------------------------------- */

static size_t _strlen(const char *s)
{
	size_t n = 0;

	if (!s)
		return (0);
	while (s[n] != '\0')
		n++;
	return (n);
}

static void puterr(const char *msg)
{
	if (msg)
		(void)write(STDERR_FILENO, msg, _strlen(msg));
}

static void die(const char *prefix, const char *detail)
{
	puterr("Error: ");
	if (prefix)
		puterr(prefix);
	if (detail)
	{
		puterr(": ");
		puterr(detail);
	}
	puterr("\n");
	exit(98);
}

/* Byte-swap helpers without C99 long-long literals (pedantic-safe) */
static uint16_t bswap16(uint16_t x)
{
	return (uint16_t)((x >> 8) | (x << 8));
}

static uint32_t bswap32(uint32_t x)
{
	return ((x & (uint32_t)0x000000FFU) << 24) |
	       ((x & (uint32_t)0x0000FF00U) << 8)  |
	       ((x & (uint32_t)0x00FF0000U) >> 8)  |
	       ((x & (uint32_t)0xFF000000U) >> 24);
}

static uint64_t bswap64(uint64_t x)
{
	/* Split into 32-bit halves, byte-swap each, then swap halves */
	uint32_t lo = (uint32_t)x;
	uint32_t hi = (uint32_t)(x >> 32);
	uint64_t hi_sw = (uint64_t)bswap32(lo); /* becomes the new high */
	uint64_t lo_sw = (uint64_t)bswap32(hi); /* becomes the new low */
	return (hi_sw << 32) | lo_sw;
}
/* The above avoids ULL suffixes. Expanded, it’s equivalent to the usual form. */

/* Human-readable mappers (match readelf -h wording where applicable) */

static const char *class_str(unsigned char c)
{
	if (c == ELFCLASS32)
		return ("ELF32");
	if (c == ELFCLASS64)
		return ("ELF64");
	return ("none");
}

static const char *data_str(unsigned char d)
{
	if (d == ELFDATA2LSB)
		return ("2's complement, little endian");
	if (d == ELFDATA2MSB)
		return ("2's complement, big endian");
	return ("Invalid data encoding");
}

static void print_version(unsigned char v)
{
	if (v == EV_CURRENT)
		printf("  %-34s %u (current)\n", "Version:", (unsigned int)v);
	else
		printf("  %-34s %u\n", "Version:", (unsigned int)v);
}

static const char *osabi_str(unsigned char o)
{
	/* Keep only symbols present on Ubuntu 20.04's elf.h; gate the rest. */
	switch (o)
	{
	case ELFOSABI_SYSV:    return ("UNIX - System V");
	case ELFOSABI_HPUX:    return ("UNIX - HP-UX");
	case ELFOSABI_NETBSD:  return ("UNIX - NetBSD");
#ifdef ELFOSABI_GNU
	case ELFOSABI_GNU:     return ("UNIX - GNU"); /* also alias of LINUX */
#endif
	case ELFOSABI_SOLARIS: return ("UNIX - Solaris");
	case ELFOSABI_AIX:     return ("UNIX - AIX");
	case ELFOSABI_IRIX:    return ("UNIX - IRIX");
	case ELFOSABI_FREEBSD: return ("UNIX - FreeBSD");
	case ELFOSABI_TRU64:   return ("UNIX - TRU64");
	case ELFOSABI_MODESTO: return ("Novell - Modesto");
	case ELFOSABI_OPENBSD: return ("UNIX - OpenBSD");
#ifdef ELFOSABI_OPENVMS
	case ELFOSABI_OPENVMS: return ("VMS - OpenVMS");
#endif
#ifdef ELFOSABI_NSK
	case ELFOSABI_NSK:     return ("HP - Non-Stop Kernel");
#endif
#ifdef ELFOSABI_AROS
	case ELFOSABI_AROS:    return ("AROS");
#endif
#ifdef ELFOSABI_FENIXOS
	case ELFOSABI_FENIXOS: return ("Fenix OS");
#endif
#ifdef ELFOSABI_CLOUDABI
	case ELFOSABI_CLOUDABI:return ("Nuxi CloudABI");
#endif
#ifdef ELFOSABI_OPENVOS
	case ELFOSABI_OPENVOS: return ("Stratus Technologies OpenVOS");
#endif
	default:               return (NULL); /* print as <unknown: xx> */
	}
}

static const char *type_base_str(uint16_t t)
{
	switch (t)
	{
	case ET_NONE: return ("NONE (None)");
	case ET_REL:  return ("REL (Relocatable file)");
	case ET_EXEC: return ("EXEC (Executable file)");
	case ET_DYN:  return ("DYN (Shared object file)");
	case ET_CORE: return ("CORE (Core file)");
	default:      return (NULL);
	}
}

/* ---------- Core printing logic ------------------------------------------ */

static void print_magic(const unsigned char *ident)
{
	int i;

	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", ident[i]);
		if (i != EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	int fd;
	ssize_t nread;
	unsigned char buf[64];
	unsigned char *id;
	unsigned char cls, data, ei_ver, osabi, abiver;
	uint16_t e_type_raw, e_type;
	unsigned long entry_ul = 0; /* print-friendly, 32/64 promoted */
	const Elf64_Ehdr *eh64;
	const Elf32_Ehdr *eh32;
	const char *ostr, *tstr;

	if (argc != 2)
		die("Usage", "elf_header elf_filename");

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		die("Can't open file", argv[1]);

	nread = read(fd, buf, sizeof(buf)); /* single read */
	if (nread < (ssize_t)sizeof(Elf32_Ehdr))
	{
		close(fd);
		die("Can't read ELF header", argv[1]);
	}
	(void)close(fd);

	/* Magic */
	id = buf;
	if (!(id[0] == 0x7f && id[1] == 'E' && id[2] == 'L' && id[3] == 'F'))
		die("Not an ELF file", argv[1]);

	print_magic(id);

	/* Basic fields from e_ident */
	cls = id[EI_CLASS];
	data = id[EI_DATA];
	ei_ver = id[EI_VERSION];
	osabi = id[EI_OSABI];
	abiver = id[EI_ABIVERSION];

	printf("  %-34s %s\n", "Class:", class_str(cls));
	printf("  %-34s %s\n", "Data:", data_str(data));
	print_version(ei_ver);

	ostr = osabi_str(osabi);
	if (ostr)
		printf("  %-34s %s\n", "OS/ABI:", ostr);
	else
		printf("  OS/ABI:%28s<unknown: %x>\n", " ", (unsigned int)osabi);

	printf("  %-34s %u\n", "ABI Version:", (unsigned int)abiver);

	/* Parse class-specific header; ensure we actually have enough bytes */
	if (cls == ELFCLASS64)
	{
		if (nread < (ssize_t)sizeof(Elf64_Ehdr))
			die("Can't read full ELF64 header", argv[1]);

		eh64 = (const Elf64_Ehdr *)buf;
		e_type_raw = eh64->e_type;
		entry_ul = (unsigned long)eh64->e_entry;

		if (data == ELFDATA2MSB)
		{
			e_type_raw = bswap16(e_type_raw);
			entry_ul = (unsigned long)bswap64((uint64_t)eh64->e_entry);
		}
		e_type = e_type_raw;
	}
	else if (cls == ELFCLASS32)
	{
		if (nread < (ssize_t)sizeof(Elf32_Ehdr))
			die("Can't read full ELF32 header", argv[1]);

		eh32 = (const Elf32_Ehdr *)buf;
		e_type_raw = eh32->e_type;
		entry_ul = (unsigned long)eh32->e_entry;

		if (data == ELFDATA2MSB)
		{
			e_type_raw = bswap16(e_type_raw);
			entry_ul = (unsigned long)bswap32((uint32_t)eh32->e_entry);
		}
		e_type = e_type_raw;
	}
	else
	{
		die("Unsupported ELF class", argv[1]);
	}

	/* Type line */
	tstr = type_base_str(e_type);
	if (tstr)
		printf("  %-34s %s\n", "Type:", tstr);
	else if (e_type >= ET_LOOS && e_type <= ET_HIOS)
		printf("  %-34s OS Specific: (%#x)\n", "Type:", (unsigned int)e_type);
	else if (e_type >= ET_LOPROC) /* avoid upper-bound warning */
		printf("  %-34s Processor Specific: (%#x)\n", "Type:", (unsigned int)e_type);
	else
		printf("  %-34s <unknown>: %u\n", "Type:", (unsigned int)e_type);

	/* Entry point address */
	if (cls == ELFCLASS64)
		printf("  %-34s 0x%lx\n", "Entry point address:", entry_ul);
	else
		printf("  %-34s 0x%lx\n", "Entry point address:", entry_ul);

	return (0);
}

