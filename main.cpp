#include <mysqlx/xdevapi.h>
#include <iostream>
#include <string>

// MySQL connection details
const std::string HOST = "localhost";
const unsigned int PORT = 33060;
const std::string USER = "root";
const std::string PASSWORD = "1234";
const std::string SCHEMA = "school";

// Function to create a session
mysqlx::Session getSession() {
    return mysqlx::Session(HOST, PORT, USER, PASSWORD);
}

// Function to create the schema if it does not exist
void createSchema(mysqlx::Session& session, const std::string& schemaName) {
    session.sql("CREATE DATABASE IF NOT EXISTS " + schemaName).execute();
    session.sql("USE " + schemaName).execute();
}

// Function to create the student table
void createStudentTable() {
    try {
        mysqlx::Session session = getSession();
        createSchema(session, SCHEMA);

        // Execute a SQL command to create the student table
        session.sql("CREATE TABLE IF NOT EXISTS student ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "name VARCHAR(100), "
                    "age INT, "
                    "major VARCHAR(50)"
                    ")").execute();

        std::cout << "Student table created successfully." << std::endl;
        session.close();
    } catch (const mysqlx::Error &err) {
        std::cerr << "ERROR: " << err.what() << std::endl;
    }
}

// Function to insert a student into the student table
void insertStudent(const std::string &name, int age, const std::string &major) {
    try {
        mysqlx::Session session = getSession();
        session.sql("USE " + SCHEMA).execute();
        mysqlx::Table table = session.getSchema(SCHEMA).getTable("student");

        table.insert("name", "age", "major").values(name, age, major).execute();

        std::cout << "Student inserted successfully." << std::endl;
        session.close();
    } catch (const mysqlx::Error &err) {
        std::cerr << "ERROR: " << err.what() << std::endl;
    }
}

// Function to get all students
void getAllStudents() {
    try {
        mysqlx::Session session = getSession();
        session.sql("USE " + SCHEMA).execute();
        mysqlx::Table table = session.getSchema(SCHEMA).getTable("student");

        mysqlx::RowResult result = table.select("id", "name", "age", "major").execute();

        for (mysqlx::Row row : result) {
            std::cout << "ID: " << row[0] << ", Name: " << row[1]
                      << ", Age: " << row[2] << ", Major: " << row[3] << std::endl;
        }

        session.close();
    } catch (const mysqlx::Error &err) {
        std::cerr << "ERROR: " << err.what() << std::endl;
    }
}

// Function to get a student by ID
void getStudentById(int id) {
    try {
        mysqlx::Session session = getSession();
        session.sql("USE " + SCHEMA).execute();
        mysqlx::Table table = session.getSchema(SCHEMA).getTable("student");

        mysqlx::RowResult result = table.select("id", "name", "age", "major")
                                        .where("id = :id")
                                        .bind("id", id)
                                        .execute();

        if (mysqlx::Row row = result.fetchOne()) {
            std::cout << "ID: " << row[0] << ", Name: " << row[1]
                      << ", Age: " << row[2] << ", Major: " << row[3] << std::endl;
        } else {
            std::cout << "Student with ID " << id << " not found." << std::endl;
        }

        session.close();
    } catch (const mysqlx::Error &err) {
        std::cerr << "ERROR: " << err.what() << std::endl;
    }
}

// Main function to demonstrate the usage of the above functions
int main() {
    // Create the student table
    createStudentTable();

    // Insert some students
    insertStudent("Alice", 20, "Computer Science");
    insertStudent("Bob", 22, "Mathematics");

    // Get all students
    getAllStudents();

    // Get a student by ID
    getStudentById(1);

    return 0;
}
