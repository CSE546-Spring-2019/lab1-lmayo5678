
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *input_file;
    FILE *output_file;
    char *search_string;
    if(argc == 4) {
        input_file = fopen(argv[1], "rb");
        output_file = fopen(argv[3], "w");
        search_string = argv[2]; 
    }else{
        printf("Error: incorrect number of parameters\n");
        printf("Usage: count $input_file $search_string $output_file\n");
        return -1;
    }
    if(!input_file){
        printf("Error opening input file. Exiting\n");
        printf("Usage: count $input_file $search_string $output_file\n");
    }
    char *buffer;
    size_t buf_size = 100;
    size_t char_len = sizeof(char); 
    buffer = calloc(buf_size, char_len);
    
    int count = 0;
    int file_size = 0;
    
    //We need to keep track of as many possible matches as there are characters in the search string.
    //For example, tttttt as input and ttt as the search string, would require 3 increments per character as it matches each of the characters in the search string. 
    int s_len = strlen(search_string);
    int *matches = calloc(s_len, sizeof(int));
    
    if( !buffer || !matches){
        printf("Error allocating memory, exiting\n");
        return -1;
    }
    
    int num_read = fread(buffer, char_len, buf_size, input_file);
    while( num_read > 0 ){
        file_size += num_read;

        for(int index = 0; index < num_read; index++){
                
            int first = 0;
            for(int s_index = 0; s_index < s_len; s_index++){
                //Here we go through matches, and compare the search string at matches[s_index]
                //This progresses through the search string, and tracks multiple at once. 
                if( (buffer[index] == (search_string[matches[s_index]] & 0xff)) && (matches[s_index] != 0|| !first)){
                    
                    if(matches[s_index] == 0){
                        first = 1;
                    }
                    matches[s_index]++;
                    
                    if(matches[s_index] == s_len){
                        matches[s_index] = 0;
                        count++;
                    }
                }else{
                    matches[s_index] = 0;
                }

            } 
        }
        num_read = fread(buffer, char_len, buf_size, input_file);
    } 
       
    //Output information to file and     
    fprintf(output_file, "File size: %d\n", file_size);
    fprintf(output_file, "%s appeared %d times\n", search_string, count);
    printf("File size: %d\n", file_size);
    printf("%s appeared %d times\n", search_string, count);
    
    free(buffer);
    free(matches);
    
    if(input_file){
        fclose(input_file);
    } 
    if(output_file){
        fclose(output_file);
    }
}
