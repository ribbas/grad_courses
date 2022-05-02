
main()
{
	char ibuffer[100];
	char obuffer[100];
	int ifd;		/* input and output file descriptors */
	int i;

	ifd = setup_client (2100);

	for (i = 0; i < 100; i++)
	{
		sprintf (obuffer, "xxxxx %02d", i);
		write (ifd, obuffer, 8);
		read (ifd, ibuffer, 8);
		ibuffer[8] = '\0';
		printf ("xxxxx: buffer is *%s*\n", ibuffer);
	}
	shutdown (ifd, 2);
	close (ifd);
}
logmsg(a1,a2,a3,a4,a5)
char *a1;
char *a2, *a3, *a4, *a5;
{
	char buffer[1000];

	strcpy (buffer, a1);
	strcat (buffer, "\n");
	printf (buffer,a2,a3,a4,a5);
}
