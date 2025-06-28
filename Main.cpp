#include<iostream>
#include<string>
using namespace std;

class user;
class page;
class post;
class date;
class activity;
struct comment;


class id {
protected:
	string ID;
public:
	id(string i = " ") :ID(i) {}
	virtual ~id() {}

	string getId() {
		return ID;
	}

	void display() {
		cout << ID << endl;
	}
};

class date {
	int d;
	int m;
	int y;

public:
	date(int dd = 5, int mm = 5, int yy = 2025) {
		d = dd;
		m = mm;
		y = yy;
	}
	~date() {}

	bool isWithinLast24Hours(const date& current)
	{
		if (y == current.y && m == current.m) {
			if (d == current.d || d == current.d - 1) {
				return true;
			}
		}
		return false;
	}

	bool isMemory(const date& current) //  by saqib
	{
		if ((y != current.y) && m == current.m)
		{
			return true;
		}
		return false;
	}


	void displayDate() {
		cout << d << "/" << m << "/" << y;
	}

	int getDay() const { return d; }
	int getMonth() const { return m; }
	int getYear() const { return y; }
};


class activity {
	int type;
	string value;
public:
	activity(int i = 0, string v = " ") {
		if (i >= 1 && i <= 4) {
			type = i;
			value = v;
		}
		else {
			type = 0;
			value = "Invalid";
			cout << "Invalid activity type. Supported types: 1 (Feeling), 2 (Thinking), 3 (Making), 4 (Celebrating)" << endl;
		}
	}
	~activity() {}

	void displayActivity() {
		if (type == 0)return;

		switch (type) {
		case 1: cout << " is Feeling " << value << endl; break;
		case 2:cout << " is Thinking about " << value << endl; break;
		case 3: cout << " is Making " << value << endl; break;
		case 4: cout << " is Celebrating " << value << endl; break;
		}

	}
};
class user : public id {
	string name;
	user** friends;
	int friendcount;
	page** pagesliked;
	int likedpagecount;
	post** posts;
	post** memory;
	int memorycount;
	int postcount;
public:


	user(string n, string i) :id(i) {
		name = n;
		friendcount = 0;
		likedpagecount = 0;
		postcount = 0;
		memorycount = 0;
		memory = nullptr;
		friends = nullptr;
		pagesliked = nullptr;
		posts = nullptr;
	}
	~user() {
		if (friends != nullptr) delete[] friends;
		if (pagesliked != nullptr) delete[] pagesliked;
		if (posts != nullptr) delete[] posts;
		if (memory != nullptr) delete[] memory;
	}

	string getName() {
		return name;
	}
	void addfriend(user* ptr) {

		user** temp = new user * [friendcount + 1];

		for (int i = 0; i < friendcount; i++) {
			temp[i] = friends[i];
		}

		temp[friendcount] = ptr;

		if (friends != nullptr) delete[] friends;

		friends = temp;
		friendcount++;
	}

	void StoreMemory(const date& current);


	//for resharing a already existing post
	void shareMemory(post* p)
	{
		if (memory != nullptr) delete[] memory;
		memory = new post * [10];
		for (int i = 0; i < 10; i++) {
			memory[i] = nullptr;
		}
		memory[memorycount] = p;
		memorycount++;

	}
	user* getFriendinfo(int i)
	{
		if (i >= 0 && i < friendcount)
		{
			return friends[i];
		}
		return nullptr;
	}

	void likepage(page* ptr); //implemented after class 

	void addpost(post* ptr) {

		post** temp = new post * [postcount + 1];

		for (int i = 0; i < postcount; i++) {
			temp[i] = posts[i];
		}

		temp[postcount] = ptr;

		delete[] posts;
		posts = temp;

		postcount++;
	}


	page* getPageInfo(int i)
	{
		if (i >= 0 && i < likedpagecount)
		{
			return pagesliked[i];
		}
		return nullptr;
	}



	int getfc()
	{
		return friendcount;
	}

	int getlc()
	{
		return likedpagecount;
	}

	int getPostCount()
	{
		return postcount;
	}

	post* getPost(int i) const
	{
		if (i >= 0 && i < postcount)
		{
			return posts[i];
		}
		return nullptr;
	}


	void displayuser() {
		cout << name << endl;
	}
	void displayfriendlist() {
		cout << name << " is friend with --" << endl;
		for (int i = 0; i < friendcount; i++) {
			cout << "[" << i + 1 << "] ";
			friends[i]->displayuser();
		}
	}
	void displaylikedpages();

	void displaypost();

};

struct comment {
	string text;
	user* commenter;
	date commentDate;
	comment(string t, user* u, int d, int m, int y) : text(t), commenter(u), commentDate(d, m, y) {}
};

class page :public id {
protected:
	string title;
	post** posts;
	int postcount;
	int likescount; // of page
	user** userlist;
	int userlistcount;
public:
	page(string n, string i) :id(i) {
		title = n;
		postcount = 0;
		likescount = 0;
		userlistcount = 0;
		posts = nullptr;
		userlist = nullptr;
	}
	~page() {
		if (posts != nullptr) delete[] posts;
		if (userlist != nullptr) delete[] userlist;
	}
	string getTitle() {
		return title;
	}

	void addpost(post* ptr);

	void displaypage() {
		cout << ID << " - " << title << endl;
	}

	void displaypageposts();

	void adduser(user* u) {
		user** temp = new user * [userlistcount + 1];

		for (int i = 0; i < userlistcount; i++) {
			temp[i] = userlist[i];
		}

		temp[userlistcount] = u;

		delete[] userlist;
		userlist = temp;

		userlistcount++;
	}

	int getPostCount()
	{
		return postcount;
	}


	void displaylikeduser() {
		cout << "Users who liked " << title << ":" << endl;
		for (int i = 0; i < userlistcount; i++) {
			userlist[i]->displayuser();
		}
	}

	post* getPost(int i) const
	{
		if (i >= 0 && i < postcount)
		{
			return posts[i];
		}
		return nullptr; // Added return for out of bounds
	}

};

class post :public id {
	string text;
	int likescount; // of post
	user** userlist;
	date DATE;
	activity* Activity;
	comment** comments;
	int commentcount;
public:
	post(string id, string t, int d, int m, int y, int activityType = 0, string activityValue = " ") :id(id), DATE(d, m, y)
	{

		userlist = nullptr;
		text = t;
		likescount = 0;
		commentcount = 0;
		comments = new comment * [10]; // Max 10 comments
		for (int i = 0; i < 10; i++) comments[i] = nullptr;
		if (activityType != 0) {
			Activity = new activity(activityType, activityValue);
		}
		else {
			Activity = nullptr; // Initialize to nullptr if no activity
		}
	}
	~post() {
		if (userlist != nullptr) delete[] userlist;
		if (Activity != nullptr) delete Activity;

		for (int i = 0; i < commentcount; i++) {
			if (comments[i] != nullptr) {
				delete comments[i];
			}
		}

	}

	void addlike(user* u) {
		user** temp = new user * [likescount + 1];

		for (int i = 0; i < likescount; i++) {
			temp[i] = userlist[i];
		}

		temp[likescount] = u;

		delete[] userlist;
		userlist = temp;

		likescount++;
	}
	void addcomment(string commented, user* commentor, int d, int m, int y) {
		if (commentcount < 10) {
			comments[commentcount] = new comment(commented, commentor, d, m, y);
			commentcount++;
		}
		else {
			cout << "Comment limit (10) reached for post ID: " << ID << endl;
		}
	}
	void displayuserlist() {
		for (int i = 0; i < likescount; i++) {
			userlist[i]->displayuser();
		}
	}

	void displaypost() {




		if (Activity != nullptr) {
			Activity->displayActivity();
		}
		cout << "             " << text << endl;
		cout << "Date: ";
		DATE.displayDate();
		cout << endl;


		cout << "Likes: " << likescount << endl;
		cout << "Comments (" << commentcount << " ):" << endl;

		for (int i = 0; i < commentcount; i++) {
			cout << " " << comments[i]->text << " by ";
			comments[i]->commenter->displayuser();
			cout << " on ";
			comments[i]->commentDate.displayDate();
			cout << endl;
		}
		cout << "--------------------------------------------\n";
	}


	void displaypostlikers()
	{
		cout << "Users who liked this post:" << endl;
		for (int i = 0; i < likescount; i++) {
			userlist[i]->displayuser();
		}
	}


	date& getdate()
	{
		return DATE;
	}


};



// Declaration after all classes defined

void user::displaypost() {

	for (int i = 0; i < postcount; i++) {
		posts[i]->displaypost();
	}
	for (int i = 0; i < memorycount; i++) {
		memory[i]->displaypost();
	}
}
void user::likepage(page* ptr) {
	if (likedpagecount < 10) {
		page** temp = new page * [likedpagecount + 1];

		for (int i = 0; i < likedpagecount; i++) {
			temp[i] = pagesliked[i];
		}

		temp[likedpagecount] = ptr;

		if (pagesliked != nullptr) delete[] pagesliked;
		pagesliked = temp;

		likedpagecount++;

		ptr->adduser(this); // Adding user in list of likecount of page
	}
	else {
		cout << "Pages like limit exceed \n page: " << ptr->getTitle() << " cannot be added" << endl;
	}
}

void user::displaylikedpages() {
	cout << name << "  has Liked the following Pages: " << endl;
	for (int i = 0; i < likedpagecount; i++) {
		cout << "[" << i + 1 << "] ";
		pagesliked[i]->displaypage();
	}
}
void page::addpost(post* ptr) {
	post** temp = new post * [postcount + 1];

	for (int i = 0; i < postcount; i++) {
		temp[i] = posts[i];
	}

	temp[postcount] = ptr;

	if (posts != nullptr) delete[] posts;
	posts = temp;

	postcount++;
}
void page::displaypageposts() {

	for (int i = 0; i < postcount; i++) {
		posts[i]->displaypost();
	}
}
void user::StoreMemory(const date& current)
{
	if (memory != nullptr) delete[] memory;
	memory = new post * [10];
	for (int i = 0; i < 10; i++) {
		memory[i] = nullptr;
	}

	memorycount = 0;

	cout << "\nFinding memories for " << name << "...\n";
	bool foundMemories = false;

	for (int i = 0; i < postcount; i++)
	{
		if (posts[i]->getdate().isMemory(current))
		{
			if (memorycount < 10) {
				memory[memorycount] = posts[i];
				memorycount++;
				foundMemories = true;
			}
		}
	}

	if (foundMemories) {
		for (int i = 0; i < memorycount; i++) {
			int yearsAgo = current.getYear() - memory[i]->getdate().getYear();
			cout << "\n=== " << yearsAgo << " years ago on this day ===\n";
			cout << name << " ";
			memory[i]->displaypost();
		}
		cout << "Total memories found: " << memorycount << endl;
	}
	else {
		cout << "No memories found for this month from previous years.\n";
	}

	cout << "\nPress Enter to continue...";
	cin.ignore();
	cin.get();
}

class SocialNetworkApp {

	date currentdate;
	user* current;


public:
	SocialNetworkApp()
	{
		current = nullptr;
	}
	~SocialNetworkApp() {

	}
	void setuser(user* obj)

	{
		current = obj;
		cout << obj->getId() << " (ID ) set as the current user\n";
	}

	void setdate(const date& d) {
		currentdate = date(d.getDay(), d.getMonth(), d.getYear());
	}

	//3
	void likeapost(post* p, user* u)
	{
		p->addlike(u);
		cout << "Post liked successfully." << endl;
	}
	//5
	void comment(post* p, string text, user* u, int d, int m, int y)
	{
		p->addcomment(text, u, d, m, y);
		cout << "Comment added successfully." << endl;
	}

	//2
	void viewhome()
	{

		const int max = 20;
		post* postlist[20];


		if (current == nullptr) {
			cout << "No user is currently logged in." << endl;
			return;
		}

		cout << "\n\n Viewing post from last 24 hours of "; currentdate.displayDate();
		bool exithome = false;

		while (!exithome)
		{
			int postcount = 0;
			cout << "\n\nViewing home of user " << current->getName(); cout << "from last 24 hours of "; currentdate.displayDate();

			// last 24 wali posts view karne ke liye . friens kee

			for (int i = 0; i < current->getfc(); i++)
			{
				user* f1 = current->getFriendinfo(i); //  return a pointer of friend user
				for (int j = 0; j < f1->getPostCount(); j++)
				{
					post* p1 = f1->getPost(j);
					if (p1->getdate().isWithinLast24Hours(currentdate)) {
						cout << "\n\n\n[" << postcount + 1 << "]";
						cout << "--------------------------------------------\n";
						cout << f1->getName(); p1->displaypost();
						cout << "\n\n";

						//adding post in a sep array for like/comment later
						if (postcount < max) {
							postlist[postcount] = p1;
							postcount++;
						}
					}
				}
			}

			// last 24 hours wli page post

			for (int i = 0; i < current->getlc(); i++)
			{
				page* pg = current->getPageInfo(i);
				for (int j = 0; j < pg->getPostCount(); j++)
				{
					post* p2 = pg->getPost(j);
					if (p2->getdate().isWithinLast24Hours(currentdate))
					{
						cout << "[" << postcount + 1 << "] "; //adding post num for selection
						cout << "\n\n\n--- " << pg->getTitle() << " ";
						p2->displaypost();
						cout << "\n\n";

						//
						if (postcount < max) {
							postlist[postcount] = p2;
							postcount++;
						}
					}
				}
			}

			if (postcount > 0) {
				int postchoice = 0;
				int actionchoice = 1;

				cout << "\nSelect a post (1-" << postcount << ") or 0 to go back: ";
				cin >> postchoice;


				while (cin.fail() || postchoice < 0 || postchoice > postcount) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid input. Please enter a number between 0 and " << postcount << ": ";
					cin >> postchoice;
				}

				if (postchoice == 0) {
					exithome = true;
					continue; // user selected 0 to go back

				}

				post* selectedpost = postlist[postchoice - 1]; // user na jonsi post select ki uska pointer


				cout << "\nSelected Post:\n";
				selectedpost->displaypost();

				cout << "\nActions:\n";
				cout << "1. Like post\n";
				cout << "2. Comment on post\n";
				cout << "3. View who liked this post\n";
				cout << "0. Back\n";
				cout << "Enter your choice: ";

				cin >> actionchoice;

				while (cin.fail() || actionchoice < 0 || actionchoice > 3) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid input. Please enter a number between 0 and 3: ";
					cin >> actionchoice;
				}

				switch (actionchoice) {
				case 1:
					likeapost(selectedpost, current);
					break;

				case 2:
				{
					string commentText = " ";
					cout << "Enter your comment: ";
					cin.ignore(); // Clear input buffer
					getline(cin, commentText);

					//add comment
					comment(selectedpost, commentText, current,
						currentdate.getDay(), currentdate.getMonth(), currentdate.getYear());
					break;
				}
				case 3:
					viewWhoLiked(selectedpost);
					break;
				case 0:
					exithome = true;
					return;
				}

			}
		}
	}


	void viewWhoLiked(post* p)
	{
		p->displayuserlist();

	}

	void viewuserpost(user* u) {

		const int max = 20;
		post* postlist[max];
		int postcount = 0;
		bool exitview = false;

		while (!exitview) {
			postcount = 0; //reset it for each new loop iterstion of user friend	

			cout << "\n Viewing posts of " << u->getName() << endl;

			for (int i = 0; i < u->getPostCount(); i++) {

				if (postcount < max) {
					postlist[postcount] = u->getPost(i);
					postcount++;
				}
			}

			for (int i = 0; i < postcount; i++) {

				cout << "\n\n\n[" << i + 1 << "]";
				cout << "--------------------------------------------\n";
				cout << u->getName(); postlist[i]->displaypost();
				cout << "\n\n";


			}

			if (postcount > 0) {
				int choice = 0;
				cout << "\nSelect a post (1-" << postcount << ") or 0 to go back: ";
				cin >> choice;

				while (cin.fail() || choice < 0 || choice > postcount) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid input. Please enter a number between 0 and " << postcount << ": ";
					cin >> choice;
				}

				if (choice == 0) {
					exitview = true;
					continue;
				}

				post* selectedpost = postlist[choice - 1];

				cout << "\nSelected Post:\n";
				selectedpost->displaypost();

				cout << "\nActions:\n";
				cout << "1. Like post\n";
				cout << "2. Comment on post\n";
				cout << "3. View who liked this post\n";
				cout << "0. Back\n";
				cout << "Enter your choice: ";

				int actionchoice = 0;
				cin >> actionchoice;

				while (cin.fail() || actionchoice < 0 || actionchoice > 3) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid input. Please enter a number between 0 and 3: ";
					cin >> actionchoice;
				}

				switch (actionchoice) {
				case 1:
					likeapost(selectedpost, current);
					break;

				case 2: {
					string commentText = "";
					cout << "Enter your comment: ";
					cin.ignore();
					getline(cin, commentText);

					comment(selectedpost, commentText, current,
						currentdate.getDay(), currentdate.getMonth(), currentdate.getYear());
					break;
				}

				case 3:
					viewWhoLiked(selectedpost);
					break;

				case 0:
					// Just continue the loop
					break;
				}
			}
			else {
				cout << "No posts to display." << endl;
				cout << "Press Enter to continue...";
				cin.ignore();
				cin.get();
				exitview = true;
			}
		}
	}

	void viewpagepost(page* u) {

		const int max = 20;
		post* postlist[max];
		int postcount = 0;
		bool exitview = false;

		while (!exitview) {

			postcount = 0;

			cout << "\n Viewing posts of " << u->getTitle() << endl;

			for (int i = 0; i < u->getPostCount(); i++) {

				if (postcount < max) {
					postlist[postcount] = u->getPost(i);
					postcount++;
				}
			}

			for (int i = 0; i < postcount; i++) {


				cout << "[" << postcount + 1 << "] "; //adding post num for selection
				cout << "\n\n\n--- " << u->getTitle() << " ";
				postlist[i]->displaypost();
				cout << "\n\n";


			}

			if (postcount > 0) {
				int choice = 0;
				cout << "\nSelect a post (1-" << postcount << ") or 0 to go back: ";
				cin >> choice;

				while (cin.fail() || choice < 0 || choice > postcount) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid input. Please enter a number between 0 and " << postcount << ": ";
					cin >> choice;
				}

				if (choice == 0) {
					exitview = true;
					continue;
				}

				post* selectedpost = postlist[choice - 1];

				cout << "\nSelected Post:\n";
				selectedpost->displaypost();

				cout << "\nActions:\n";
				cout << "1. Like post\n";
				cout << "2. Comment on post\n";
				cout << "3. View who liked this post\n";
				cout << "0. Back\n";
				cout << "Enter your choice: ";

				int actionchoice = 0;
				cin >> actionchoice;

				while (cin.fail() || actionchoice < 0 || actionchoice > 3) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid input. Please enter a number between 0 and 3: ";
					cin >> actionchoice;
				}

				switch (actionchoice) {
				case 1:
					likeapost(selectedpost, current);
					break;

				case 2: {
					string commentText = "";
					cout << "Enter your comment: ";
					cin.ignore();
					getline(cin, commentText);

					comment(selectedpost, commentText, current,
						currentdate.getDay(), currentdate.getMonth(), currentdate.getYear());
					break;
				}

				case 3:
					viewWhoLiked(selectedpost);
					break;

				case 0:
					// Just continue the loop
					break;
				}
			}
			else {
				cout << "No posts to display." << endl;
				cout << "Press Enter to continue...";
				cin.ignore();
				cin.get();
				exitview = true;
			}
		}
	}
};


int main()
{
	date currentdate(10, 5, 2025);
	SocialNetworkApp s1;

	s1.setdate(currentdate);

	user** u = new user * [12];

	u[0] = new user("Ali", "User1");
	u[1] = new user("Ahmed", "User2");
	u[2] = new user("Amar", "User3");
	u[3] = new user("Ayan", "User4");
	u[4] = new user("Ameer", "User5");
	u[5] = new user("Zain", "User6");
	u[6] = new user("Hamza", "User7");
	u[7] = new user("Aliyar", "User8");
	u[8] = new user("Amna", "User9");
	u[9] = new user("Ayesha", "User10");
	u[10] = new user("Eman", "User11");
	u[11] = new user("Asim", "User12");


	// Add friends

	//user 1
	u[0]->addfriend(u[1]);
	u[0]->addfriend(u[2]);
	u[0]->addfriend(u[3]);
	u[0]->addfriend(u[4]);
	u[0]->addfriend(u[5]);
	u[0]->addfriend(u[6]);

	//user2
	u[1]->addfriend(u[0]);
	u[1]->addfriend(u[2]);
	u[1]->addfriend(u[7]);

	//user 3
	u[2]->addfriend(u[0]);
	u[2]->addfriend(u[1]);
	u[2]->addfriend(u[4]);
	u[2]->addfriend(u[3]);

	//user 4
	u[3]->addfriend(u[0]);
	u[3]->addfriend(u[5]);
	u[3]->addfriend(u[8]);

	//user 5
	u[4]->addfriend(u[0]);
	u[4]->addfriend(u[2]);
	u[4]->addfriend(u[9]);

	//user 6
	u[5]->addfriend(u[0]);
	u[5]->addfriend(u[3]);
	u[5]->addfriend(u[10]);

	//user 7
	u[6]->addfriend(u[1]);
	u[6]->addfriend(u[2]);
	u[6]->addfriend(u[3]);
	u[6]->addfriend(u[4]);
	u[6]->addfriend(u[5]);

	//user 8
	u[7]->addfriend(u[0]);
	u[7]->addfriend(u[2]);
	u[7]->addfriend(u[3]);
	u[7]->addfriend(u[4]);
	u[7]->addfriend(u[5]);

	//user 9
	u[8]->addfriend(u[0]);
	u[8]->addfriend(u[1]);
	u[8]->addfriend(u[2]);
	u[8]->addfriend(u[4]);
	u[8]->addfriend(u[5]);
	u[8]->addfriend(u[6]);
	u[8]->addfriend(u[7]);

	//user 10
	u[9]->addfriend(u[0]);
	u[9]->addfriend(u[2]);
	u[9]->addfriend(u[4]);
	u[9]->addfriend(u[6]);
	u[9]->addfriend(u[7]);

	//user 11
	u[10]->addfriend(u[1]);
	u[10]->addfriend(u[2]);
	u[10]->addfriend(u[3]);
	u[10]->addfriend(u[6]);
	u[10]->addfriend(u[7]);

	//user 12
	u[11]->addfriend(u[0]);
	u[11]->addfriend(u[2]);
	u[11]->addfriend(u[4]);
	u[11]->addfriend(u[6]);
	u[11]->addfriend(u[7]);



	// Create pages
	page** p = new page * [12];
	p[0] = new page("Star Plus", "p0");
	p[1] = new page("National Geographic", "p1");
	p[2] = new page("History Channel", "p2");
	p[3] = new page("Cartoon Network", "p3");
	p[4] = new page("Discovery", "p4");
	p[5] = new page("HBO", "p5");
	p[6] = new page("Netflix", "p6");
	p[7] = new page("Amazon Prime", "p7");
	p[8] = new page("Disney+", "p8");
	p[9] = new page("BBC Earth", "p9");
	p[10] = new page("Animal Planet", "p10");
	p[11] = new page("CNN", "p11");


	// Like pages
	u[0]->likepage(p[0]);
	u[0]->likepage(p[1]);
	u[0]->likepage(p[2]);
	u[0]->likepage(p[3]);
	u[0]->likepage(p[4]);


	u[1]->likepage(p[0]);
	u[1]->likepage(p[2]);
	u[1]->likepage(p[6]);
	u[1]->likepage(p[7]);

	u[2]->likepage(p[1]);
	u[2]->likepage(p[3]);
	u[1]->likepage(p[6]);
	u[1]->likepage(p[7]);

	u[3]->likepage(p[2]);
	u[3]->likepage(p[4]);
	u[3]->likepage(p[7]);

	u[4]->likepage(p[5]);
	u[4]->likepage(p[8]);

	u[5]->likepage(p[9]);
	u[5]->likepage(p[10]);


	// Create posts with activities
	post** posts = new post * [20];

	// Older posts
	posts[0] = new post("post1", "\"HELLO WORLD!\"", 25, 10, 2017, 1, "Happy"); // Feeling Happy
	posts[1] = new post("post2", "\"CHECK OUT THIS NEW TECH!\"", 9, 5, 2023, 4, "A birthday"); // Celebrating A birthday
	posts[2] = new post("post3", "\"LOVING THE WEATHER TODAY.\"", 14, 3, 2022, 2, "Grateful");
	posts[3] = new post("post4", "\"JUST SAW AN AMAZING MOVIE!\"", 7, 11, 2023, 3, "Excited");
	posts[4] = new post("post5", "\"STUDY MODE: ON!\"", 1, 1, 2024, 1, "Motivated");
	posts[5] = new post("post6", "\"ROAD TRIP TO THE MOUNTAINS!\"", 18, 6, 2020, 2, "Adventurous");

	// Recent posts (last 24 hours - May 9-10, 2025)
	posts[6] = new post("post7", "\"ENJOYING A GOOD BOOK RIGHT NOW.\"", 9, 5, 2025, 2, "Relaxed");
	posts[7] = new post("post8", "\"JUST LAUNCHED OUR NEW PRODUCT TODAY!\"", 10, 5, 2025, 3, "Excited");
	posts[8] = new post("post9", "\"LATE NIGHT CODING SESSION IN PROGRESS!\"", 10, 5, 2025, 2, "Productive");
	posts[9] = new post("post10", "\"GAME NIGHT WITH FRIENDS TONIGHT!\"", 10, 5, 2025, 1, "Joyful");
	posts[10] = new post("post11", "\"COOKING SOMETHING NEW FOR DINNER!\"", 9, 5, 2025, 3, "Creative");
	posts[11] = new post("post12", "\"GRADUATED TODAY! FINALLY DONE WITH EXAMS.\"", 10, 5, 2025, 4, "Proud");

	// More posts with varied dates
	posts[12] = new post("post13", "\"LEARNING TO PLAY GUITAR.\"", 5, 4, 2025, 3, "Determined");
	posts[13] = new post("post14", "\"MISS THE OLD DAYS OF SIMPLE TECH.\"", 20, 3, 2025, 2, "Nostalgic");
	posts[14] = new post("post15", "\"JUST ADOPTED A NEW PUPPY!\"", 10, 5, 2025, 1, "Overjoyed");
	posts[15] = new post("post16", "\"WORKING ON A NEW SIDE PROJECT.\"", 9, 5, 2025, 3, "Focused");
	posts[16] = new post("post17", "\"HEADING TO THE BEACH THIS WEEKEND!\"", 10, 5, 2025, 2, "Excited");
	posts[17] = new post("post18", "\"WATCHING THE LATEST SEASON OF MY FAVORITE SHOW.\"", 9, 5, 2025, 1, "Entertained");
	posts[18] = new post("post19", "\"STARTED LEARNING TO CODE.\"", 8, 5, 2025, 3, "Challenged");
	posts[19] = new post("post20", "\"IT'S MY BIRTHDAY TODAY!\"", 10, 5, 2025, 4, "Birthday celebration");


	// User1 has several posts
	u[0]->addpost(posts[0]);
	u[1]->addpost(posts[1]);
	u[0]->addpost(posts[7]);
	u[1]->addpost(posts[8]);
	u[1]->addpost(posts[9]);
	u[0]->addpost(posts[14]);

	// User2 has some posts including recent ones
	u[2]->addpost(posts[15]);
	u[2]->addpost(posts[16]);

	// Other users have posts
	u[2]->addpost(posts[2]);
	u[2]->addpost(posts[9]);
	u[2]->addpost(posts[10]);
	u[3]->addpost(posts[16]);
	u[3]->addpost(posts[17]);

	u[3]->addpost(posts[3]);
	u[3]->addpost(posts[10]);
	u[3]->addpost(posts[17]);

	u[4]->addpost(posts[4]);
	u[4]->addpost(posts[11]);
	u[4]->addpost(posts[18]);

	u[5]->addpost(posts[5]);
	u[5]->addpost(posts[6]);
	u[5]->addpost(posts[19]);

	// Add some posts to pages (including recent posts)
	post* pagePost1 = new post("pagePost1", "\"NEW DOCUMENTARY SERIES COMING NEXT MONTH!\"", 9, 5, 2025, 4, "New Release");
	post* pagePost2 = new post("pagePost2", "\"BEHIND THE SCENES LOOK AT OUR LATEST FILM.\"", 10, 5, 2025);
	post* pagePost3 = new post("pagePost3", "\"CHECK OUT OUR SCHEDULE FOR THIS WEEKEND.\"", 10, 5, 2025, 2, "Weekend Plans");
	post* pagePost4 = new post("pagePost4", "\"THROWBACK TO OUR FIRST BROADCAST IN 1980.\"", 8, 5, 2025);


	p[0]->addpost(pagePost1);
	p[1]->addpost(pagePost2);
	p[3]->addpost(pagePost3);
	p[5]->addpost(pagePost4);


	// Add likes to posts - make some posts very popular
	// Many likes for post7 (recent)
	posts[6]->addlike(u[0]);
	posts[6]->addlike(u[1]);
	posts[6]->addlike(u[2]);
	posts[6]->addlike(u[3]);
	posts[6]->addlike(u[4]);

	// Several likes for post8 (recent)
	posts[7]->addlike(u[1]);
	posts[7]->addlike(u[2]);
	posts[7]->addlike(u[5]);

	// Other likes
	posts[0]->addlike(u[1]);
	posts[0]->addlike(u[2]);
	posts[0]->addlike(u[3]);
	posts[0]->addlike(u[4]);

	posts[1]->addlike(u[2]);
	posts[1]->addlike(u[0]);
	posts[1]->addlike(u[3]);
	posts[1]->addlike(u[1]);

	posts[2]->addlike(u[0]);
	posts[2]->addlike(u[1]);
	posts[2]->addlike(u[3]);

	posts[3]->addlike(u[0]);
	posts[3]->addlike(u[3]);
	posts[3]->addlike(u[4]);

	posts[4]->addlike(u[0]);
	posts[4]->addlike(u[5]);
	posts[4]->addlike(u[2]);

	posts[4]->addlike(u[2]);
	posts[4]->addlike(u[3]);

	posts[5]->addlike(u[4]);
	posts[5]->addlike(u[1]);

	posts[6]->addlike(u[0]);

	posts[7]->addlike(u[5]);

	posts[8]->addlike(u[2]);

	posts[9]->addlike(u[0]);
	posts[9]->addlike(u[4]);

	posts[10]->addlike(u[0]);

	posts[11]->addlike(u[5]);

	posts[12]->addlike(u[0]);

	posts[13]->addlike(u[5]);
	posts[14]->addlike(u[0]);

	posts[15]->addlike(u[5]);
	posts[16]->addlike(u[0]);

	posts[17]->addlike(u[5]);
	posts[18]->addlike(u[0]);



	posts[19]->addlike(u[0]);
	posts[19]->addlike(u[1]);
	posts[19]->addlike(u[2]);
	posts[19]->addlike(u[3]);
	posts[19]->addlike(u[4]);

	// Add likes to page posts
	pagePost1->addlike(u[0]);
	pagePost1->addlike(u[1]);
	pagePost1->addlike(u[3]);

	pagePost2->addlike(u[0]);
	pagePost2->addlike(u[2]);

	pagePost3->addlike(u[0]);
	pagePost3->addlike(u[4]);
	pagePost3->addlike(u[5]);

	pagePost4->addlike(u[1]);
	pagePost4->addlike(u[3]);
	pagePost4->addlike(u[6]);



	// Add comments with user and date - add many comments to some posts
	// Comments on older posts
	posts[0]->addcomment("Great post!", u[2], 26, 10, 2017);
	posts[0]->addcomment("Love it!", u[3], 12, 10, 2017);
	posts[0]->addcomment("Well done!", u[5], 13, 10, 2017);


	posts[1]->addcomment("Keep it up!", u[0], 10, 5, 2023);
	posts[1]->addcomment("Tnks for sharing!", u[9], 4, 5, 2023);
	posts[1]->addcomment("Awesome tech!", u[1], 15, 3, 2022);

	posts[2]->addcomment("Perfect day!", u[0], 10, 5, 2023);
	posts[2]->addcomment("Beautiful Day, isn't it?", u[9], 4, 5, 2023);
	posts[2]->addcomment("Loving the vibee!", u[1], 15, 3, 2022);

	posts[3]->addcomment("Just watched. Mind blown", u[2], 10, 5, 2023);
	posts[3]->addcomment("Totally worth it.", u[3], 9, 5, 2023);
	posts[3]->addcomment("Highly recommend!", u[4], 13, 3, 2022);


	posts[4]->addcomment("Brain loading... ", u[6], 10, 5, 2023);
	posts[4]->addcomment("No pain, no gain", u[9], 7, 5, 2023);
	posts[4]->addcomment("Focus time! You got this", u[2], 2, 3, 2022);



	posts[5]->addcomment("Mountains calling!", u[2], 10, 5, 2023);
	posts[5]->addcomment("That fresh mountain air hits different", u[3], 7, 5, 2023);
	posts[5]->addcomment("Vibes unmatched ", u[4], 2, 3, 2022);



	// Comments on recent posts (last 24 hours)
	posts[6]->addcomment("What book are you reading?", u[0], 9, 5, 2025);
	posts[6]->addcomment("I love that author too!", u[2], 9, 5, 2025);
	posts[6]->addcomment("You should try the sequel also.", u[4], 10, 5, 2025);

	posts[7]->addcomment("Congratulations on the launch!", u[0], 10, 5, 2025);
	posts[7]->addcomment("Can't wait to try it out!", u[3], 10, 5, 2025);

	posts[9]->addcomment("Count me in next time!", u[0], 10, 5, 2025);
	posts[9]->addcomment("What games did you play?", u[1], 10, 5, 2025);
	posts[9]->addcomment("We should organize one for next weekend too!", u[5], 10, 5, 2025);

	posts[11]->addcomment("Congratulations!", u[0], 10, 5, 2025);
	posts[11]->addcomment("Well deserved! You worked so hard.", u[1], 10, 5, 2025);
	posts[11]->addcomment("Party time! ", u[2], 10, 5, 2025);
	posts[11]->addcomment("So proud of you!", u[3], 10, 5, 2025);


	posts[12]->addcomment("Rockstar in the making ", u[0], 10, 5, 2025);
	posts[12]->addcomment("Strings and dreams .", u[7], 10, 5, 2025);
	posts[12]->addcomment("Music begins! ", u[8], 10, 5, 2025);

	posts[13]->addcomment("Take me back.", u[7], 10, 5, 2025);
	posts[13]->addcomment("Old good days! ", u[8], 10, 5, 2025);

	posts[14]->addcomment("So cute! What breed?", u[1], 10, 5, 2025);
	posts[14]->addcomment("Post pictures please!", u[2], 10, 5, 2025);


	posts[15]->addcomment("Keep grinding, it’ll pay off soon ", u[2], 10, 5, 2025);

	posts[16]->addcomment("Sounds like the perfect weekend", u[2], 10, 5, 2025);

	posts[17]->addcomment("Don’t spoil it!", u[2], 10, 5, 2025);

	posts[18]->addcomment("Welcome to the world of code", u[2], 10, 5, 2025);

	posts[19]->addcomment("Happy Birthday!", u[0], 10, 5, 2025);
	posts[19]->addcomment("Many happy returns!", u[1], 10, 5, 2025);
	posts[19]->addcomment("Hope you have a wonderful day!", u[2], 10, 5, 2025);

	// Comments on page posts
	pagePost1->addcomment("Looking forward to it!", u[0], 9, 5, 2025);
	pagePost1->addcomment("Will it be available worldwide?", u[2], 10, 5, 2025);

	pagePost3->addcomment("Thanks for posting the schedule!", u[0], 10, 5, 2025);
	pagePost3->addcomment("Can't wait for the Saturday lineup!", u[3], 10, 5, 2025);


	// User shared a memory
	u[0]->shareMemory(posts[2]); // User1 shared User3's post




	int usernum;
	int choice;

	cout << "HI!!!! Welcome to social media app by Malik Abdul Rehman and Saqib Jutt." << endl;
	while (true) {
		cout << "\n====== Social Media Application ======" << endl;
		cout << "Availabe User" << endl;
		for (int i = 0; i < 12; i++) {
			cout << i + 1 << " : "; u[i]->displayuser();
		}
		cout << "Select User (enter serial num)" << endl;

		do {

			cin >> usernum;
			if (usernum < 0 || usernum>12) {
				cout << "Error input again" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
		} while (usernum < 0 || usernum>12);

		s1.setuser(u[usernum - 1]);

		bool changeuser = false;
		while (!changeuser) {
			cout << "\n===== User Menu =====" << endl;
			cout << "1. View Home" << endl;
			cout << "2. select profile" << endl;

			cout << "\nEnter your choice: ";

			cin >> choice;
			while (cin.fail() || choice < 1 || choice > 2) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid input. Please enter a number between 1 and 3: ";
				cin >> choice;
			}
			if (choice == 2) {
				changeuser = false;
				while (!changeuser) {
					cout << "\n===== Profile =====" << u[usernum - 1]->getName() << " =====" << endl;

					cout << "1. View Friend list" << endl;
					cout << "2. View Liked Pages" << endl;
					cout << "3. View Timeline" << endl;
					cout << "4. View Memories" << endl;
					cout << "5. Log Out" << endl;

					cout << "\nEnter your choice: ";
					cin >> choice;
					while (cin.fail() || choice < 1 || choice > 5) {
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "Invalid input. Please enter a number between 1 and 3: ";
						cin >> choice;
					}

					switch (choice) {
					case 1: {
						u[usernum - 1]->displayfriendlist();
						int friendChoice = 0;
						cout << "\nSelect a friend to view their posts (1-" << u[usernum - 1]->getfc() << ") or 0 to go back: ";
						cin >> friendChoice;

						while (cin.fail() || friendChoice < 0 || friendChoice > u[usernum - 1]->getfc()) {
							cin.clear();
							cin.ignore(10000, '\n');
							cout << "Invalid input. Please enter a number between 0 and " << u[usernum - 1]->getfc() << ": ";
							cin >> friendChoice;
						}

						if (friendChoice > 0) {
							user* selectedFriend = u[usernum - 1]->getFriendinfo(friendChoice - 1);
							s1.viewuserpost(selectedFriend);
						}
						break;
					}
					case 2:
					{
						u[usernum - 1]->displaylikedpages();

						// Option to view a page's posts
						int pageChoice = 0;
						cout << "\nSelect a page to view its posts (1-" << u[usernum - 1]->getlc() << ") or 0 to go back: ";
						cin >> pageChoice;

						while (cin.fail() || pageChoice < 0 || pageChoice > u[usernum - 1]->getlc()) {
							cin.clear();
							cin.ignore(10000, '\n');
							cout << "Invalid input. Please enter a number between 0 and " << u[usernum - 1]->getlc() << ": ";
							cin >> pageChoice;
						}

						if (pageChoice > 0) {
							page* selectedPage = u[usernum - 1]->getPageInfo(pageChoice - 1);
							s1.viewpagepost(selectedPage);
						}
						break;
					}
					case 3:
						cout << "Timeline " << u[usernum - 1]->getName() << endl;
						u[usernum - 1]->displaypost();
						cout << "\nPress Enter to continue...";
						cin.ignore();
						cin.get();
						break;
					case 4:
						cout << "checking memories for : " << u[usernum - 1]->getName() << endl;
						u[usernum - 1]->StoreMemory(currentdate);
						break;
					case 5:
						changeuser = true;
						break;

					}
				}
			}
			else {
				cout << "\n===== Home page =====" << endl;
				s1.viewhome();

			}
		}



	}
}