// this is a program to implement density based clustering algorithm
// Author: Rajat Sharma
// Date: march, 2018

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct
{
    int category;
    int clusterID;
}datapoint[50];

main()
{
    FILE *fp = fopen("data.txt","r");
    int dataset[50][2], i=0, j=0, k=0, Minpts, Eps, no_of_datapoint=0;

    // to retrieve data from file to dataset matrix
    while(!feof(fp))
    {
        fscanf(fp,"%d %d",&dataset[i][0], &dataset[i][1]);
        no_of_datapoint++;
        i++;
    }

    printf("\nEnter the value of Minpts : ");
    scanf("%d", &Minpts);
    printf("Enter the value of Eps : ");
    scanf("%d", &Eps);

    int distance[no_of_datapoint], neighbour[no_of_datapoint], count=0, clusterCount=1;

    // scanning starts from here
    for(i=0;i<no_of_datapoint;i++)
    {
        // storing the distance of all the points in the dataset with point i.
        for(j=0;j<no_of_datapoint;j++)
        {
            distance[j] = sqrt(pow(dataset[i][0]-dataset[j][0],2) + pow(dataset[i][1]-dataset[j][1],2));
        }

        // storing the index of datapoint which is neighbor of point i.
        for(j=0;j<no_of_datapoint;j++)
        {
            if(distance[j]<=Eps)
            {
                neighbour[count]=j;
                count++;
            }
        }

        if(count > Minpts)
        {
            // datapoint i is a core point
            datapoint[i].category = 0;

            // if the selected core point have a clusterID
            if(datapoint[i].clusterID!=0)
            {
                for(j=0;j<count;j++)
                {
                    datapoint[neighbour[j]].clusterID = datapoint[i].clusterID;
                }
            }
            else
            {
                // checking whether any neighbor points have any clusterID
                for(j=0;j<count;j++)
                {
                    if(datapoint[neighbour[j]].clusterID!=0)
                    {
                        // assigning the same clusterID to the selected core point
                        datapoint[i].clusterID = datapoint[neighbour[j]].clusterID;

                        // assigning the same clusterID to the neighbours too.
                        for(k=0;k<count;k++)
                        {
                            datapoint[neighbour[k]].clusterID = datapoint[i].clusterID;
                        }

                    }
                }
            }

            // if the core point doesn't get any clusterID from neighbor
            if(datapoint[i].clusterID == 0)
            {
                datapoint[i].clusterID = clusterCount;

                // assign same clusterID of core point to the neighbors.
                for(j=0;j<count;j++)
                {
                    datapoint[neighbour[j]].clusterID = clusterCount;
                }
                clusterCount++;
            }
        }
        else    // if the point i is a noise point
        {
            datapoint[i].category = 1;
            datapoint[i].clusterID = 0;
        }

        count=0;
    }

    // printing the the output.
    for(i=0;i<no_of_datapoint;i++)
    {
		printf("data: (%d,%d)\tCategory: %d\tclusterID: %d\n",dataset[i][0], dataset[i][1], datapoint[i].category, datapoint[i].clusterID);
	}
}
