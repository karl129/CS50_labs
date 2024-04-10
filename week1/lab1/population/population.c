#include <stdio.h>
#include <stdlib.h>
// 得到种群起始数量
long *get_sizes();

// 计算所需年
int calc_years(long start, long end);

int main(void)
{
    int years;
    long *nums = get_sizes();
    long start = nums[0], end = nums[1];
    years = calc_years(start, end);
    printf("Years: %i\n", years);

    free(nums);
    return 0;
}

long *get_sizes()
{
    long *nums = (long *) malloc(sizeof(long) * 2);
    if (nums == NULL)
    {
        return 1;
    }
    do
    {
        printf("Start size: ");
        scanf("%li", &nums[0]);
    }
    while (nums[0] < 9);

    do
    {
        printf("End size: ");
        scanf("%li", &nums[1]);
    }
    while (nums[0] > nums[1]);
    return nums;
}

int calc_years(long start, long end)
{
    long now = start;
    int years = 0;
    while (now < end)
    {
        int increase_num = now / 3;
        int reduce_num = now / 4;
        now = now - reduce_num + increase_num;
        years++;
    }
    return years;
}
