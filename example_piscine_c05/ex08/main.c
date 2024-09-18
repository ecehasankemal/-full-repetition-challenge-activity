# include <stdio.h>

int my_ten_queens_puzzle(void);

int
    main(void)
{
    int result;

    result = my_ten_queens_puzzle();
    printf("Number of solutions = %d\n", result);
    return (0);
}