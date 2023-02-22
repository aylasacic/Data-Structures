// Initialization of the Admin class and two functions realted to Admin

class Admin{
private:
	int Admin_ID;
    std::string First_name;
    std::string Last_name;
    std::string Username;
    std::string Password;

public:
    // COnstructor
    Admin(int admin_id, std::string first_name, std::string last_name, std::string username, std::string password);
    
    // DEstructor
    ~Admin();
    
    int getAdminID();
    
    std::string getUsername();
    
    std::string getPassword();
    
    void output();
};

void adminOptions();
void addAdmin(Admin *ClassArray []);
