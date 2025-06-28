
# 🧾 Console-Based Social Media App

A simple **console application** that simulates a basic social media platform. Users can post updates, like and comment on posts, view interactions, and manage their profile through a text-based interface.

---

## 🌟 Features

- **Post Creation**: Users can create text-based posts.
- **Like and Comment**: Posts can be liked or commented on by others.
- **Post Interaction**: View who liked and commented on each post.
- **User Profile Management**:
  - View **Friend List**
  - View **Liked Pages**
  - View **Timeline**
  - View **Memories**
- **Date & Activity Metadata**: All posts and comments are timestamped.

---

## 🏗️ Project Structure

```
mainfile.cpp       # Contains complete logic of the application
user.txt           # Stores user data (name, ID, friends, liked pages)
page.txt           # Stores page data (name, ID, liked by users)
post.txt           # Stores all posts with meta info
comment.txt        # Stores comments with timestamps and authorship
memories.txt       # Stores shared memories
```

---

## ▶️ How to Run

1. Open the project in **Visual Studio** or any standard **C++ IDE**.
2. Build and run the project.
3. Interact via the command-line interface.

---

## 📚 Concepts Used

- **Object-Oriented Programming (OOP)**: Classes for User, Post, Comment, and Page.
- **Encapsulation and Abstraction**: User-friendly interface while hiding logic details.
- **Menus and Navigation**: Text-based menu system for feature access.
- **Date/Time Handling**: Post/comment timestamps.

---

## 🔧 Potential Improvements

- ✅ Add persistent data storage using file I/O or SQLite.
- ✅ Implement login/logout functionality for multi-user support.
- ✅ Enable searching friends or posts.
- ✅ Add user settings and custom profile pictures (ASCII art or placeholder).
- ✅ Add admin functionality for moderating content.
- ✅ Add pagination for long timelines.
- ✅ Enhance UI with color (using ANSI codes).
