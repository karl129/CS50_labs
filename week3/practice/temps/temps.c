// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities_buble(void);
void sort_cities_select(void);
void swap(avg_temp temp[], int j, int k);

void merge(avg_temp temps[], int start, int middle, int end);
void sort_cities_merge(int strart, int end);
int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    // sort_cities_buble();
    // sort_cities_select();

    sort_cities_merge(0, NUM_CITIES - 1);

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
// 冒泡排序
void sort_cities_buble(void)
{
    // Add your code here
    bool flag;
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        flag = false;
        for (int j = 0; j < NUM_CITIES - 2 - i; j++)
        {
            if (temps[j].temp < temps[j + 1].temp)
            {
                swap(temps, j, j + 1);
                flag = true;
            }
        }
        if (!flag)
            break;
    }
    return;
}

// 选择排序
void sort_cities_select(void)
{
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        int big_index = i;
        for (int j = i; j < NUM_CITIES; j++)
        {
            if (temps[big_index].temp < temps[j].temp)
                big_index = j;
        }
        swap(temps, i, big_index);
    }
}

void swap(avg_temp temp[], int j, int k)
{
    avg_temp tempt = temp[j];
    temp[j] = temp[k];
    temp[k] = tempt;
}

// 归并排序
avg_temp new_temps[NUM_CITIES];

void sort_cities_merge(int start, int end)
{
    if (start >= end)
        return;
    else
    {
        int middle = start + (end - start) / 2;
        sort_cities_merge(start, middle);
        sort_cities_merge(middle + 1, end);
        merge(temps, start, middle, end);
    }
}

void merge(avg_temp temps_[], int start, int middle, int end)
{
    int i = start, j = middle + 1;
    int index = start;
    // 两两比较
    while (i <= middle && j <= end)
    {
        if (temps_[i].temp < temps_[j].temp)
        {
            new_temps[index] = temps_[j];
            j++;
        }
        else
        {
            new_temps[index] = temps_[i];
            i++;
        }
        index++;
    }
    // 没得比的时候直接写入剩下的
    while (i <= middle)
    {
        new_temps[index] = temps_[i];
        i++;
    }
    while (j <= end)
    {
        new_temps[index] = temps_[j];
        j++;
    }
    // 更新
    for (int k = start; k <= end; k++)
    {
        temps[k] = new_temps[k];
    }
}
