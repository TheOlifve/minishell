int	main(void)
{
	int	i;
	int	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (i < 100)
		{
		
		}
		exit (0);
	}
	while (wait(pid) < 0)
		;
	wh
}