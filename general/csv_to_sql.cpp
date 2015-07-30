#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <sqlite3.h> 

static void start_daemon()
{
	pid_t pid;

	/* Fork off the parent process */
	pid = fork();

	/* An error occurred */
	if (pid < 0)
		exit(EXIT_FAILURE);

	/* Success: Let the parent terminate */
	if (pid > 0)
		exit(EXIT_SUCCESS);

	pid = setsid();

	/* On success: The child process becomes session leader */
	if (pid < 0)
		exit(EXIT_FAILURE);

	/* Catch, ignore and handle signals */
	//TODO: Implement a working signal handler */
	signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	/* Fork off for the second time*/
	pid = fork();

	/* An error occurred */
	if (pid < 0)
		exit(EXIT_FAILURE);

	/* Success: Let the parent terminate */
	if (pid > 0)
		exit(EXIT_SUCCESS);

	/* Close all open file descriptors */
	int x;
	for (x = sysconf(_SC_OPEN_MAX); x>0; --x)
	{
		close (x);
	}
}

int update_table( const char * file_name, const char * table_name )
{
	FILE * output_file;
	output_file = fopen("file_name.txt", "w");
	
	if ( output_file )
	{
		fprintf(output_file, "file %s\ntable %s\n", file_name, table_name);
	}


	sqlite3 *db;
	char *zErrMsg = 0;
	int return_code;

	return_code = sqlite3_open("tickets.db", &db);

	if( return_code )
	{
		fprintf(output_file, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else
	{
		fprintf(output_file, "Opened database successfully\n");
	}

	get_csv( file_name );
	insert( db, csv_table );

	sqlite3_close(db);
	fclose(output_file);
}


int main( int argc, const char ** argv )
{
	start_daemon();

	if ( argc > 2 )
	{
		update_table( argv[1], argv[2] );
	}

	return EXIT_SUCCESS;
}
