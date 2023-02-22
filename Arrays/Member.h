// Intialization of the Member Class and functions relating to member.
class Member{
private:
    int Member_ID;
    std::string First_name;
    std::string Last_name;
    std::string Username;
    std::string Password;
    
public:
    // Constructor
    Member(int member_id, std::string first_name, std::string last_name, std::string username, std::string password);
    
    // Destructor
    ~Member();
    
    int getMemberID();
    
    std::string getUsername();
    
    std::string getPassword();
    
    void output();
};

void memberOptions();
void addMember(Member *ClassArray []);
int returnID(Member *ClassArray [], std::string username, std::string password);

