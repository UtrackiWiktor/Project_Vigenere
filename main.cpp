/*
 *	Copyright Bart³omiej Piura & Pawe³ Szafraniec 2020
 */
#include <string>
#include <vector>
#include <iostream>

 /*
	 Make something that such that class will be polymorphic.
 */
class Component {
public:
	virtual void write_message(const std::string& message)
	{
		std::cout << "Class name: " << typeid(*this).name() << "\nMessage: " << message << std::endl;
	}
};

/*
	Make something that such that class will be polymorphic.
*/
class Describable {
public:
	virtual void write_message(const std::string& message)
	{
		std::cout << "Class name: " << typeid(*this).name() << "\nMessage: " << message << std::endl;
	}
};

class Writer : public Component, public Describable {
public:

	/*
	Should write given message to console. Name of this class should also be written, but it can't be hardcoded (use RTTI).
	*/
	virtual void write_message(const std::string& message)
	{
		std::cout << "Class name: " << typeid(*this).name() << "\nMessage: " << message << std::endl;
	}
};

class WriterWithHistory : public Writer, public Describable {
public:

	/*
		Call 'write_message' from Writer class, and store given message. (Some extra fields should be added)
	*/
	std::vector<std::string> mssgs;

	void write_message(const std::string& message)
	{
		std::cout << "Class name: " << typeid(*this).name() << "\nMessage: " << message << std::endl;
		mssgs.push_back(message);
	}

	/*
		Return all stored messages.
	*/
	const std::vector<std::string>& get_messages()
	{
		return mssgs;
	}
};

/*
	Pring history of the given writer. If it hasn't history, inform user about it.
*/
void printHistory(Writer* w)
{
	if (auto temp = dynamic_cast<WriterWithHistory*>(w))
	{
		std::cout << "Messages:\n";

		for (const auto i : temp->get_messages())
		{
			std::cout << i << std::endl;
		}
		return;
	}

	std::cout << "No messages to print!\n";
	return;
}


class Logger {
public:
	/*
		Store somewhere name of the type of the given component.
	*/
	std::string component_name;

	Logger(Component* o) : component_name(typeid(o).name())
	{

	}

	/*
		Print give message and stored type name.
	*/
	void print(std::string m)
	{
		std::cout << "Message: " << m << "\nTypename: " << component_name << std::endl;
	}
};

/*
	1. Create object of Component, Writer and WriterWithHistory.
	2. Call write_message on Writer and WriterWithHistory few times with different messages.
	3. Pass both writers to printHistory function. What happened?
	4. Create logger for each of created objects.
	5. Call print function for each created logger.
	6. Using dynamic_cast cast a pointer of WriterWithHistory to Component pointer
		and Describable pointer. Write to the console values of both pointers. What is the result? Why?
*/
int main()
{
	Component comp;
	Writer writ;
	WriterWithHistory writhist;
	std::cout << "Firsty task:\n";
	comp.write_message("This is a comp message.");
	std::cout << std::endl;
	writ.write_message("This is a writ message.");
	std::cout << std::endl;
	writhist.write_message("This is a writhist message.");
	std::cout << std::endl;

	std::cout << "\nSecond task:\n";
	writ.write_message("This is a second writ message.");
	std::cout << std::endl;
	writ.write_message("This is a third writ message.");
	std::cout << std::endl;
	writ.write_message("This is a fourth writ message. And the last of them");
	std::cout << std::endl;

	writhist.write_message("This is a second writ message.");
	std::cout << std::endl;
	writhist.write_message("This is a third writ message.");
	std::cout << std::endl;
	writhist.write_message("This is a fourth writ message. And the last of them");
	std::cout << std::endl;

	std::cout << "\nThird task:\n";
	std::cout << "Write messages:\n";
	printHistory(&writ);
	std::cout << "\nWritehist messages:\n";
	printHistory(&writhist);

	std::cout << "\nFourth task:\n";
	Logger log_writ(&writ);
	Logger log_writhist(&writhist);
	Logger log_comp(&comp);

	std::cout << "\nFifth task:\n";
	log_comp.print("logger comp");
	log_writ.print("logger writ");
	log_writhist.print("logger writhist");

	std::cout << "\nSixth task:\n";
	auto p_writhist_comp = dynamic_cast<Component*>(&writhist);
	auto p_hist_desc = dynamic_cast<Describable*>(&writhist);
	std::cout << "Pionter comp: " << p_writhist_comp << "\nPointer desc: " << p_hist_desc << std::endl;

	system("PAUSE");
	return 0;
}