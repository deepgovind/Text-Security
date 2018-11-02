static BOOL character_encode ( unsigned char c, FILE *infile, FILE *outfile)
{
	int	 i;

	for (i=0; i<8; i++) 
	{
	    int		bit = ((c & (128 >> i)) != 0) ? 1 : 0;

	    if (!compress_bit (bit, infile, outfile))
		return (FALSE);
	}

	return (TRUE);
}
 
static BOOL message_string_encode (const char	*msg, FILE *infile, FILE *outfile)
{
	compress_init ();

	while (*msg != '\0') 
	{
	    if (!character_encode (*msg, infile, outfile))
		return (FALSE);
	    msg++;
	}

	return (compress_flush (infile, outfile));
}
 
static BOOL message_fp_encode ( FILE *msg_fp, FILE *infile, FILE *outfile)
{
	int		c;

	compress_init ();
	while ((c = fgetc (msg_fp)) != EOF)
	    if (!character_encode (c, infile, outfile))
		return (FALSE);

	if (ferror (msg_fp) != 0) 
	{
	    perror ("Message file");
	    return (FALSE);
	}

	return (compress_flush (infile, outfile));
}
 

int mainstart(int argc,char *argv[])
{
	int		c;
	int		optind;
	
	BOOL		space_flag = FALSE;
	char		*passwd = NULL;
	char		*message_string = NULL;
	FILE		*message_fp = NULL;
	FILE		*infile = stdin;
	FILE		*outfile = stdout;

	optind = 1;
	for (optind = 1; optind < argc
 
			&& (argv[optind][0] == '-' || argv[optind][0] == '/');
 
						optind++) {
	    char	c = argv[optind][1];
	    char	*optarg;

	  
	    switch (c) {
		case 'C':
		    compress_flag = TRUE;
		    break;
 		case 'f':
		    if (argv[optind][2] != '\0')
			optarg = &argv[optind][2];
		    else if (++optind == argc) {
			errflag = TRUE;
			break;
		    } else
			optarg = argv[optind];

		    if ((message_fp = fopen (optarg, "r")) == NULL) {
			perror (optarg);
			errflag = TRUE;
		    }
		    break;
		case 'm':
		    if (argv[optind][2] != '\0')
			optarg = &argv[optind][2];
		    else if (++optind == argc) {
			errflag = TRUE;
			break;
		    } else
			optarg = argv[optind];

		    message_string = optarg;
		    break;
		case 'p':
		    if (argv[optind][2] != '\0')
			optarg = &argv[optind][2];
		    else if (++optind == argc) {
			errflag = TRUE;
			break;
		    } else
			optarg = argv[optind];

		    passwd = optarg;
		    break;
		default:
			sprintf(ErroeM," Error ! , Connect to Devloper ");
		   	MessageBox(mainW,ErroeM,"Error !",MB_OK|MB_ICONERROR); 
			errflag = TRUE;
		    break;
	    }

	    if (errflag)
		break;
	}
 
	if (passwd != NULL)
	    password_set (passwd);

	if (optind < argc) {
	    if ((infile = fopen (argv[optind], "r")) == NULL) {
		perror (argv[optind]);
		return 1;
	    }
	}

	if (optind + 1 < argc) 
	{
	    if ((outfile = fopen (argv[optind + 1], "w")) == NULL)
		{
		  perror (argv[optind + 1]);
		  return 1;
	    }
	}

	if (space_flag)
	{
	    space_calculate (infile);
	} 
	else if (message_string != NULL)
	{
	    if (!message_string_encode (message_string, infile, outfile))
		return 1;
	}
	else if (message_fp != NULL)
	{
	    if (!message_fp_encode (message_fp, infile, outfile))
		return 1;
	    fclose (message_fp);
	} 
	else
	{
	    if (!message_extract (infile, outfile))
		return 1;
	}

	if (outfile != stdout)
	    fclose (outfile);
	if (infile != stdout)
	    fclose (infile);

	 
	return 0;
}
