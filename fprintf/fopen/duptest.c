#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
int main( )
{
   int old;
   FILE *new;
   old = dup( 1 );   // 取标准输出句柄  
   if( old == -1 )
   {
      perror( "dup( 1 ) failure" );
      exit( 1 );
   }
   write( old, "This goes to stdout first\r\n", 27 );
   if( ( new = fopen( "data", "w" ) ) == NULL )
   {
      puts( "Can't open file 'data'\n" );
      exit( 1 );
   }
   if( -1 == dup2( fileno( new ), 1 ) )//把文件的描述符给到1,1就不代表stdout了
   {
      perror( "Can't dup2 stdout" );
      exit( 1 );
   }
   system( "ls -l" );
   puts( "This goes to file 'data'\r\n" );
   fflush( stdout );
   fclose( new );
   dup2( old, 1 ); // 恢复
   puts( "This goes to stdout\n" );
   puts( "The file 'data' contains:" );
   //system( "type data" );
   system( "file data" );
}

