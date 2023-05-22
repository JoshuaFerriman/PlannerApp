// PlannerApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "GUI.h"



int main()
{
    std::cout << "Hello World!\n";

    DatabaseAccessor databaseAccessor("test");
    databaseAccessor.CreateTable(users);

    std::vector<std::string> fieldValues = { "JohnDoe", "password123", "abcd1234" };

    databaseAccessor.TableINSERT(users, fieldValues);


    User user;
    user.TestGenerateSalt();
    user.TestGenerateSalt();
    user.TestGenerateSalt();

    GUI gui;
    gui.InitialiseGUI();
    gui.MainLoop();
    gui.CloseGUI();
    
    return 0;



    /*ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);*/
    
    /*Table users{
      "USERS",
      "CREATE TABLE USERS("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "PASS           TEXT    NOT NULL);",
      "INSERT INTO USERS(ID, NAME, PASS)",
      "SELECT * from USERS"
    };*/

    /*databaseAccessor.CreateTable(users);*/
    

  /*  std::vector<std::string> sql{
    "VALUES (1, 'Paul', 'Blue'); ",
    "VALUES (2, 'Allen', 'Goosberries'); ",
    "VALUES (3, 'Teddy', 'Ripe');",
    "VALUES (4, 'Mark', 'Yellow');"
    };*/


    /*databaseAccessor.TableINSERT(users, sql);

    std::string sqlSelectStatement = "SELECT * from USERS";

    databaseAccessor.TableSELECT(users);*/

}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

