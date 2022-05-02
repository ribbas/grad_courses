#define SERVER_FIRST 1
#define CLIENT_FIRST 0
main()
{
	char ibuffer[100];
	char obuffer[100];
	int ifd, ofd;		/* input and output file descriptors */
	int i;

	get_socket_pair (2100, 2101, &ifd, &ofd, SERVER_FIRST, "pluto.jhuapl.edu");

	for (i = 0; i < 100; i++)
	{
		read (ifd, ibuffer, 8);
		ibuffer[8] = '\0';
		printf ("try1: buffer is *%s*\n", ibuffer);
		sprintf (obuffer, "hello %02d", i);
		write (ofd, obuffer, 8);
	}
	socket_shutdown();
	close (ifd);
	close (ofd);
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
