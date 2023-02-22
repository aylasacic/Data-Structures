// Declaration of the FitnessClass Class
class FitnessClass{
private:
    int Class_ID;
    std::string Class_name;
    std::string Class_date;
    std::string Class_time;
    int Max_capacity;
    int Room_number;
    int *List_Members;
    
public:
    // Constructor
    FitnessClass(int class_id, std::string class_name, std::string class_date, std::string class_time, int max_cap, int room_nr);
    // Destructor
    ~FitnessClass();
    
    // Getters and Setters
    int getFitnessClassID();

    std::string getFitnessClassName();
    
    std::string getFitnessClassTime();
    
    std::string getFitnessClassDate();
    
    int getFitnessClassRoomNr();
    
    int getMaxCap();
    
    void printList();
    
    void setClassID(int id);
    
    void setClassName(std::string class_name);
    
    void setClassDate(std::string class_date);
    
    void setClassTime(std::string class_time);
    
    void setMaxCap(int max_cap);
    
    void setRoomNr(int room_nr);
    
    void addMember(int id);
    
    void printMembers();
    
    bool check_vacancy();
    
    bool memberInClass(int id);
    
    void removeMember(int id);
    
    void print();
    
    void output();
};

// Declaration of functions which relate to the Fitness class.
void addFitnessClass(FitnessClass *ClassArray []);
bool idExists(FitnessClass *ClassArray[], int &id);
bool validInput(char value[], std::string type);
void updateClassDetails(FitnessClass *ClassArray[]);
void deleteFitnessClass(FitnessClass *ClassArray []);
void viewClassesWithVacancies(FitnessClass *ClassArray[]);
void bookAClass(FitnessClass *ClassArray[], int current_ID);
void CancelABooking(FitnessClass *ClassArray[], int current_ID);
