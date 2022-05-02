#define SERVER_FIRST 1
#define CLIENT_FIRST 0
main()
{
	char ibuffer[100];
	char obuffer[100];
	int ifd, ofd;		/* input and output file descriptors */
	int i;

	local_get_socket_pair (2101, 2100, &ifd, &ofd, CLIENT_FIRST);

	for (i = 0; i < 100; i++)
	{
		sprintf (obuffer, "hello %02d", i);
		write (ofd, obuffer, 8);
		read (ifd, ibuffer, 8);
		ibuffer[8] = '\0';
		printf ("try: buffer is *%s*\n", ibuffer);
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
