# PassFort

#### Video Link: https://youtu.be/gsVE2kqYU3M

**Description:**

    This idea came to me through the course of understanding this course. I feel more drawn towards cybersecurity and related fields after taking this
course. Starting as a complete beginner, who couldn't even really understand beyond what GUIs show us, now I am exploring Linux commands understanding networks, learning about various vulnerabilities and how to exploit them.
    One of the most important things that I realised is that our passwords are our biggest weaknesses, no matter how secure we make the systems, a bad
password can put the whole thing in jeopardy. Human nature is the biggest vulnerability. A simple solution to that is a password manager that performs the following functions.
    This application is mainly designed for everyday users who are not that familiar with using computers and belong to the group who mostly write
their passwords down somewhere, maybe in a "passwords.txt" if tech-savvy or on a paper kept safely in their desk. This app aims to be an alternate to
those exact things.
    Now they just have to remember that one password for their username and they can access all their stored passwords easily. I've taken care to
store the passwords in an encrypted text form and also masking it. And not even the user can see the passwords at a glance, you can simply copy the
password to the clipboard and paste it in the password field, ensuring usability as well as security. No typing, no selecting, just clicking buttons.
Along with this, when we make a new entry, at that time the password is visible so that you can check and double check before committing it to the
memory. Just in case something happens, you can delete the whole entry with a single click.
    Again, this is meant specifically for the people not so faimilar with computers and need handholding. Everything is kept simple, clear, conscise
and most importantly, right there, on the screen.

        - Account is kept secure with one username and one password stored in a hash form
        - Accept website, username and password
        - Encrypt the input password, delete the original and save the encrypted one in a sql database
        - Whenever the user wants to login, they simply have to copy password, the app will decrypt and and copy it to user's cliboard
        - Even the user won't be able to see their unencrypted versions
        - Aim is to create a simple GUI so that it is accessible even to a layman

    Now we will be doing this in several steps, I will be using python to code under the hood, tkniter for the GUI, Fernet for encrypting and
decrypting the stored passwords, SHA256 from hashlib for hashing the main password, secrets for generating a random salt value and sqlit3 for
maintaining the databases.

**db.py**

    In this, we have implemented all the database functions such as creating, updating, fetching and deleting data for each unique user. There are
two tables. The first is app_users which will store the login information of all the users registered on the application. This will be used to find and verify users before letting them in to their personalised dashboards.
    The second table we created is the user_data. This stores the website, username and the hashed password according to the particular user_id. The
user can easily add new entries and retrieve stored data unique to them, this allows ease and at the same time safeguards against anyone accessing the
data of other users. This is what is displayed on the user's dashboard.
    This is sort of the main behind the scenes. All the password hashing, encryption and decryption is done here only.

**main.py**

    Mostly to just jumpstart everything, ensure table creation the first thing, does nothing other than hand over things to the gui.py login screen.
Helped a lot while debugging and launching the GUI window.

**gui.py**

    Main meat of the app, this is what the user opens up to. Takes in username and password, shows the correct error messages and also prompts the
user to register incase their username is not in the given database.
    Contains the login window and register new user window and basically, take in, hashes or encrypts the relevant information and passes it on to
the relevant db.py functions to be entered into the database.

**user_dashboard.py**

    This is what the user sees after a successful login. Mainly displays the user_data table and provides basic functionality like adding a new entry
, deleting entries, decrypting the encrypted passwords to the clipboard.
    Pretty straightforward and user friendly, most of the time spent by the user will be on this page.
