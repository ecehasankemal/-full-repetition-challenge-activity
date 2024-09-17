char
    *my_strcapitalize(char *str)
{
    int count;

    count = 0;
    while (str[count])
    {
         if ((count == 0 || !(str[count - 1] >= 'a' && str[count - 1] <= 'z') && 
             !(str[count - 1] >= 'A' && str[count - 1] <= 'Z')) 
             && (str[count] >= 'a' && str[count] <= 'z'))
                str[count] -= 32;
        else if (str[count] >= 'A' && str[count] <= 'Z'
            && (count > 0 && (str[count - 1] >= 'a' && str[count - 1] <= 'z')))
            str[count] += 32;
        count++;
    }
    return (str);
}