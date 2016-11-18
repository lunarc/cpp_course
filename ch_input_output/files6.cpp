#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct particle {
    double x;
    double y;
    double mass;
};

int main()
{
    srand((unsigned)time(0));
    
    ofstream particlesFile("particles.dat", ios::out | ios::binary);
    
    particle p;
    
    for (int i=0; i<10; i++)
    {
        p.x = 100.0*(double)rand()/(double)RAND_MAX;
        p.y = 100.0*(double)rand()/(double)RAND_MAX;
        p.mass = 1.0 + (double)rand()/(double)RAND_MAX;
        
        particlesFile.write((char*)&p, sizeof(p));
    }
    
    particlesFile.close();
    
    ifstream inputParticlesFile("particles.dat", ios::in | ios::binary );
    
    int recordSize = sizeof(p);
    
    if (inputParticlesFile.is_open())
    {
        inputParticlesFile.seekg(0);
        inputParticlesFile.seekg(5 * recordSize);
        inputParticlesFile.read((char*)&p, sizeof(p));
        
        cout << "x = " << p.x;
        cout << ", y = " << p.y;
        cout << ", m = " << p.mass << endl;
    }
    else
        cout << "Could not open file." << endl;
    
    inputParticlesFile.close();
}