#include <stdio.h> // printf, putchar
#include <stdlib.h> // atoi
#include <getopt.h> // getopt_long

void printHelp()
{
	printf
	(
"\
{} enclose mandatory arguments. [] enclose optional arguments.\n\
repeat - repeat a character sequence.\n\
repeat --version - print the version information.\n\
repeat --help - print this help message.\n\
repeat {-n 'number of repeats'} [-s 'string to repeat'] [-f]\n\
Examples:\n\
repeat -n 42 - print '=' 42 times, where 12 can be any positive integer.\n\
repeat -n 34 -s Hi - print 'Hi' 34 times, where 34 can be any positive integer.\n\
repeat -s A\\ Message -n 10 -f - print 'A\\ Message' 10 times and end it with a linefeed.\n\
"
	);
}

void printVersion()
{
	printf("repeat v1.2.0:2015.03.11\n");
}

int main(int argc, char *argv[])
{
	static struct option options[] =
	{
		{"help",			no_argument,         0,  'h' },
		{"version",			no_argument,         0,  'v' },
		{"f",				no_argument,		 0,  'f' },
		{"s",				required_argument,   0,  's' },
		{"n",				required_argument,   0,  'n' },
		{"c",				required_argument,   0,  'c' }
	};

	int long_index = 0;
	int opt = 0;

	int repeats = -1;
	int is_s_specified = 0;
	char *string;
	int oust_line_feed = 0;

	while
	(
		(opt = getopt_long
			(
				argc,
				argv,
				"c:fhn:s:v",
				options,
				&long_index
			)
		) != -1
	)
	{
		switch (opt)
		{
			case 'h':
				printHelp();
				exit(EXIT_SUCCESS);
				break;
			case 'v':
				printVersion();
				exit(EXIT_SUCCESS);
				break;
			case 'f':
				oust_line_feed = 1;
				break;
			case 's':
				string = optarg;
				is_s_specified = 1;
				break;
			case 'n':
				repeats = atoi(optarg);
				break;
			case 'c':
                string = optarg;
                is_s_specified = -1;
                break;
			default:
				exit(EXIT_FAILURE);
				break;
		}
	}
	if (repeats < 0)
	{
		printf("You must specify '-n' with a natural(0) number. E.g.: 'repeat -n 20'.\n");
		exit(EXIT_FAILURE);
	}
	if (is_s_specified == 1)
		for (int i = 0; i < repeats; ++i)
			printf("%s", string);
    else if (is_s_specified == -1)
        for (int i = 0; i < repeats; ++i)
            putchar(string[0]);
	else if (repeats > -1)
		for (int i = 0; i < repeats; ++i)
			putchar('=');
	if (oust_line_feed)
		putchar('\n');
}
