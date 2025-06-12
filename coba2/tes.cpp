#include <iostream>
#include <fstream>
#include <ctime>


using namespace std;

const int MAX = 100;


class Queue {

    private:
        int queue[MAX];
        int front, rear;
    public:
        Queue(){
            front = 0;
            rear = -1;
        }

        bool isEmpty(){
            return front > rear || front == -1;
        }

        bool isFull(){
            return rear == MAX - 1;
        }

        void enqueue(int data){
            if (isFull()){
                cout << "Antrian penuh!" << endl;
            } else{
                rear++;
                queue[rear] = data;
                cout << "Data " << data << " telah ditambahkan ke antrian." << endl;
            }
        }

        int dequeue(){
            if (front > rear || front == -1){
                cout << "Antrian kosong!" << endl;
                return -1;
            } else {
                int data = queue[front];
                front++;
                cout << "Data " << data << " telah dihapus dari antrian." << endl;
                return data;
            }
        }

        void display(){
            if(isEmpty()){
                cout << "Antrian Kosong!" << endl;
            } else {
                cout << "Isi Antrian: ";
                for(int i = front; i <=rear; i++){
                    cout << queue[i] << " ";
                }
                cout<<endl;
            }
        }
};

int main(){
    Queue q;

    q.enqueue(10);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();

    q.dequeue();
    q.display();

    q.enqueue(40);
    q.display();

    return 0;
}