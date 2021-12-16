#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string key;
char ciphertext[0];

int check_key(string KEY);
int user_input(void);

int main(int argc, string argv[])
{
    // If there are no entries from the user
    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    // set value of user input to key
    key = argv[1];
    
    // check If the number of characters is less than 26
    if (strlen(key) < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    /*
    Obtain the error code in error_code,
    
    code #1
    If there are repeated characters inside the key.
    
    code #2
    If it is one of the values it is not alphabetical.
    */
    int error_code = check_key(key);
    
    
    // Check the error code
    if (error_code == 1)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    else if (error_code == 2)
    {
        
        printf("Key must only contain alphabetic characters.\n");  
        return 1;

    }
    
    // If the key is successfully verified
    else if (error_code == 0)
    {
        if (user_input() == 0)
        {
            printf("ciphertext: %s\n", ciphertext);
            return 0;
        }
        else
        {
            printf("ciphertext:\n");
            return 1;
        }
    }
}

int check_key(string KEY)
{   
    
    for (int i = 0; i <= 24; i++)
    {
        
        if (isalpha(KEY[i]) && isalpha(KEY[25]))
        {
            
            for (int r = i + 1 ; r <= 25; r++)
            {
                
                if (KEY[i] == KEY[r])
                {
                    // return error code 1
                    return 1;
                }
               
            }
            
        }
        else
        {
            // return error code 2
            return 2;
            
        }
        
    }
    
    // this is code valid.
    return 0;
    
}

int user_input(void)
{
    // get text from user input to encrypt
    string plaintext = get_string("plaintext: ");
    
    // Verify that the user has typed anything
    if (strlen(plaintext) == 0)
    {
        return 1;
    }
    
    // Start the iteration loop to start the letter replacement process
    for (int r = 0; r <= strlen(plaintext) - 1; r++)
    {
        // Create the index to reach the required letter
        int index = 0;
        
        // Check if it is white space
        if (isspace(plaintext[r]))
        {
            ciphertext[r] = ' ';
        }
        // Check if it is number
        else if (isdigit(plaintext[r]))
        {
            ciphertext[r] = plaintext[r];
        }
        // Check if it is a special character
        else if (isalnum(plaintext[r]) == 0)
        {
            ciphertext[r] = plaintext[r];
        }
        
        for (int c = 97; c <= 122; c++)
        {
            if (tolower(plaintext[r]) == c)
            {
                // printf("this char %c as index = %i \n", c ,index);
                
                if (islower(plaintext[r]))
                {
                    ciphertext[r] = tolower(key[index]);
                }
                else
                {
                    ciphertext[r] = toupper(key[index]); 
                }
                
            }
            
            index += 1;
        }
    }

    // Encryption successful
    return 0;
}