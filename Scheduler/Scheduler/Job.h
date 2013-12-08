//
//  Job.h
//  Scheduler
//

class Job
{
public:
    // Create job with weight and length
    Job();
    Job(int weight, int length);
    
    int getWeight() const;
    int getLength() const;
    
    void print();
    
    // Overriden less than/greater than
    bool operator< (const Job &job) const;
    bool operator> (const Job &job) const;
    bool operator== (const Job &job) const;
    bool operator!= (const Job &job) const;
    
private:
    float compareVal() const;
    int weight, length;
};