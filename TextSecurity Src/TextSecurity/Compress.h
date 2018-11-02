#ifndef COMPRESS_H
#define COMPRESS_H

#include <string.h>
 
static const char	*huffcodes[256] = {
#include "huffcode.h"
};

static int		compress_bit_count;
static int		compress_value;
static unsigned long	compress_bits_in;
static unsigned long	compress_bits_out;
 
void compress_init(void)
{
	compress_bit_count = 0;
	compress_value = 0;
	compress_bits_in = 0;
	compress_bits_out = 0;

	encrypt_init ();
}

BOOL compress_bit ( int bit, FILE *inf, FILE *outf)
{
	if (!compress_flag)
	    return (encrypt_bit (bit, inf, outf));

	compress_bits_in++;
	compress_value = (compress_value << 1) | bit;

	if (++compress_bit_count == 8)
	{
	    const char	*s;

	    for (s = huffcodes[compress_value]; *s != '\0'; s++)
		{
		int	bit;

		if (*s == '1')
		    bit = 1;
		else if (*s == '0')
		    bit = 0;
		else 
		{
		   sprintf(ErroeM," Illegal Huffman character '%c'\n",*s);
		   	MessageBox(mainW,ErroeM,"Error !",MB_OK|MB_ICONERROR); 
		     return (FALSE);
		}

		if (!encrypt_bit (bit, inf, outf))
		    return (FALSE);
		compress_bits_out++;
	    }

	    compress_value = 0;
	    compress_bit_count = 0;
	}

	return (TRUE);
}
 
BOOL compress_flush ( FILE *inf, FILE *outf) 
{
	if (compress_bit_count != 0 && !quiet_flag)
	{
		    sprintf(ErroeM,"Warning: residual of %d bits not compressed\n",compress_bit_count);
		   //	MessageBox(mainW,ErroeM,"Error !",MB_OK|MB_ICONERROR); 
		   
	}
	if (compress_bits_out > 0 && !quiet_flag)
	{
	    double	cpc = (double) (compress_bits_in - compress_bits_out)
					/ (double) compress_bits_in * 100.0;

	    if (cpc < 0.0)
		{
			  char te[100];
              sprintf (te,"Compression enlarged data by %.2f%% - recommend not using compression\n", -cpc);
			   strcat(ErroeM,te);
   
		}
	    else
		{
			   char te[100];
               sprintf (te,"Compressed by %.2f%%\n", cpc);
			   strcat(ErroeM,te);

			 
		} 
	}
 	return (encrypt_flush (inf, outf));
}


/*
 * Local variables used for output.
 */

static int	output_bit_count;
static int	output_value;


/*
 * Initialize the output variables.
 */

static void output_init (void)
{
	output_bit_count = 0;
	output_value = 0;
}

/*
 * Output a single bit.
 */

static BOOL output_bit ( int	 bit, FILE *outf )
{
	output_value = (output_value << 1) | bit;

	if (++output_bit_count == 8)
	{   
		char te[4];
		sprintf(te,"%c",output_value);
		strcat(Stri,te);
	 
	    if (fputc (output_value, outf) == EOF)
		{
		  perror ("Output file");
		  return (FALSE);
	    }

	    output_value = 0;
	    output_bit_count = 0;
	}

	return (TRUE);
}


/*
 * Flush the contents of the output routines.
 */

static BOOL output_flush ( FILE *outf)
{
	if (output_bit_count > 2 && !quiet_flag)
	{
		char te[100];

		sprintf(te, "Warning: residual of %d bits not output\n", output_bit_count);
		strcat(ErroeM,te);
		SetWindowText(mainW,te);
	}
	    

	return (TRUE);
}


/*
 * Local variables used for uncompression.
 */

static int	uncompress_bit_count;
static char	uncompress_value[256];


/*
 * Initialize the uncompression routines.
 */

void uncompress_init (void)
{
	uncompress_bit_count = 0;

	output_init ();
}


/*
 * Find the Huffman code string that matches.
 */

static int huffcode_find(const char	*str)
{
	int		i;

	for (i=0; i<256; i++)
	    if (strcmp (str, huffcodes[i]) == 0)
		return (i);

	return (-1);
}


/*
 * Uncompress a single bit.
 */

BOOL
uncompress_bit (int bit, FILE *outf)
{
	int		code;

	if (!compress_flag)
	    return (output_bit (bit, outf));

	uncompress_value[uncompress_bit_count++] = bit ? '1' : '0';
	uncompress_value[uncompress_bit_count] = '\0';

	if ((code = huffcode_find (uncompress_value)) >= 0) 
	{
	    int		i;

	    for (i=0; i<8; i++)
		{
		int	b = ((code & (128 >> i)) != 0) ? 1 : 0;

		if (!output_bit (b, outf))
		    return (FALSE);
	    }

	    uncompress_bit_count = 0;
	}

	if (uncompress_bit_count >= 255)
	{
		      char te[100];
		        sprintf (te,"Error: Huffman uncompress buffer overflow\n");
			  strcat(ErroeM,te);
			 //   MessageBox(mainW,ErroeM,"Compresion Error ! ",MB_OK|MB_ICONERROR); 
	    
	    return (FALSE);
	}

	return (TRUE);
}

/*
 * Flush the contents of the uncompression routines.
 */

BOOL uncompress_flush ( FILE *outf)
{
	if (uncompress_bit_count > 2 && !quiet_flag)
	{
		char te[100];
		sprintf(ErroeM, "Warning: residual of %d bits not uncompressed\n",uncompress_bit_count);
		strcat(ErroeM,te);
		SetWindowText(mainW,te);
	}
	  
	return (output_flush (outf));
}

#endif