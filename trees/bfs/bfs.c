#include<stdio.h>
#include<stdlib.h>

int bfsCount = 0, cyclic = 0;
int count = 0;
int orderCount = 0;

int graph[100][100], visited[100];

void resetVisited(int n){
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
}

void bfs(int n, int start){

    int queue[100], parent[100];
    int front = 0, rear = 0;

    visited[start] = 1;
    count++;

    queue[rear] = start;
    parent[rear] = -1;
    rear++;

    while(front < rear){

        start = queue[front];
        int parentNode = parent[front];
        front++;

        printf("-->%c", start + 65);

        for(int i = 0; i < n; i++){

            orderCount++;

            if(i != parentNode && graph[start][i] && visited[i]){
                cyclic = 1;
            }

            if(graph[start][i] && visited[i] == 0){

                visited[i] = 1;
                count++;

                queue[rear] = i;
                parent[rear] = start;
                rear++;
            }
        }
    }
}

void bfs1(int n, int start){

    int queue[100], parent[100];
    int front = 0, rear = 0;

    visited[start] = 1;
    count++;

    queue[rear] = start;
    parent[rear] = -1;
    rear++;

    while(front < rear){

        start = queue[front];
        int parentNode = parent[front];
        front++;

        for(int i = 0; i < n; i++){

            orderCount++;

            if(i != parentNode && graph[start][i] && visited[i]){
                cyclic = 1;
            }

            if(graph[start][i] && visited[i] == 0){

                visited[i] = 1;
                count++;

                queue[rear] = i;
                parent[rear] = start;
                rear++;
            }
        }
    }
}

void tester(){

    int n;

    printf("Enter the number of nodes in the graph:\n");
    scanf("%d", &n);

    printf("Enter the Adjacency Matrix:\n");

    for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){
            scanf("%d", &graph[i][j]);
        }
    }

    resetVisited(n);

    printf("\nThe Adjacency Matrix:\n");

    for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){
            printf("%d ", graph[i][j]);
        }

        printf("\n");
    }

    bfsCount = 0;
    cyclic = 0;
    count = 0;
    orderCount = 0;

    printf("\nBreadth First Search Traversal:\n");

    bfsCount++;
    bfs(n, 0);

    if(count == n){

        printf("\nGraph is connected.\n");
    }
    else{

        printf("\nGraph is not connected.\n");

        int start = 1;

        while(count != n && start < n){

            if(visited[start] == 0){

                bfsCount++;
                bfs(n, start);
                printf("\n");
            }

            start++;
        }
    }

    printf("\nThe number of components in the graph is %d\n", bfsCount);

    if(cyclic){
        printf("The graph is cyclic\n");
    }
    else{
        printf("The graph is acyclic\n");
    }
}

void ploter(int k){

    FILE *f1 = fopen("BFSBEST.txt", "a");
    FILE *f2 = fopen("BFSWORST.txt", "a");

    int v, start;

    for(v = 1; v <= 10; v++){

        resetVisited(v);

        /*
            k = 0 -> Complete Graph
            k = 1 -> Linear Graph
        */

        if(k == 0){

            for(int i = 0; i < v; i++){

                for(int j = 0; j < v; j++){

                    if(i != j)
                        graph[i][j] = 1;
                    else
                        graph[i][j] = 0;
                }
            }
        }

        if(k == 1){

            for(int i = 0; i < v; i++){

                for(int j = 0; j < v; j++){
                    graph[i][j] = 0;
                }
            }

            for(int i = 0; i < v - 1; i++){

                graph[i][i + 1] = 1;
                graph[i + 1][i] = 1;
            }
        }

        bfsCount = 0;
        cyclic = 0;
        count = 0;
        orderCount = 0;

        bfsCount++;
        bfs1(v, 0);

        if(count != v){

            start = 1;

            while(count != v && start < v){

                if(visited[start] == 0){

                    bfsCount++;
                    bfs1(v, start);
                }

                start++;
            }
        }

        if(k == 0)
            fprintf(f1, "%d\t%d\n", v, orderCount);
        else
            fprintf(f2, "%d\t%d\n", v, orderCount);
    }

    fclose(f1);
    fclose(f2);

    printf("Data written successfully to files.\n");
}

int main(){

    while(1){

        int key;

        printf("\nENTER THE CHOICE\n");
        printf("1. TO TEST BFS\n");
        printf("2. TO PLOT\n");
        printf("OTHER TO EXIT\n");

        scanf("%d", &key);

        switch(key){

            case 1:
                tester();
                break;

            case 2:

                for(int i = 0; i < 2; i++){
                    ploter(i);
                }

                break;

            default:
                exit(0);
        }
    }

    return 0;
}
