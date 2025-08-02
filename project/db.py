import sqlite3
import base64
import hashlib
from cryptography.fernet import Fernet

# create a connection function, which we call on everytime we need to connect to the database


def connection():
    return sqlite3.connect("log.db")

# Generate a Fernet key from username


def generate_user_key(username):
    key_base = hashlib.sha256(username.encode()).digest()
    return base64.urlsafe_b64encode(key_base)

# Encrypt and decrypt functions


def encrypt_password(password, username):
    fernet = Fernet(generate_user_key(username))
    return fernet.encrypt(password.encode()).decode()


def decrypt_password(encrypted_password, username):
    fernet = Fernet(generate_user_key(username))
    return fernet.decrypt(encrypted_password.encode()).decode()

# here we create tables


def create_tables():
    con = connection()
    cursor = con.cursor()

    # this creates a table where we store the user login info
    cursor.execute(
        "CREATE TABLE IF NOT EXISTS app_users(id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, pass_hash TEXT, salt TEXT)")

    # usable info for each user
    cursor.execute("CREATE TABLE IF NOT EXISTS user_data(id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, username TEXT, website TEXT, password TEXT, FOREIGN KEY(user_id) REFERENCES app_users(id))")

    con.commit()
    con.close()


# create a new user
def create_user(username, pass_hash, salt):
    conn = connection()
    cursor = conn.cursor()

    cursor.execute("INSERT INTO app_users (username, pass_hash, salt) VALUES (?, ?, ?)",
                   (username, pass_hash, salt))

    conn.commit()
    conn.close()

# find a user (from login)


def get_user(username):
    con = connection()
    cursor = con.cursor()

    cursor.execute("SELECT id, pass_hash, salt FROM app_users WHERE username = ?", (username,))
    result = cursor.fetchone()

    con.close()

    return result

# now we will add, fetch and delete entries


def add_password_entry(user_id, website, username, password):
    con = connection()
    cursor = con.cursor()
    encrypted_password = encrypt_password(password, username)

    cursor.execute("INSERT INTO user_data (user_id, website, username, password) VALUES (?, ?, ?, ?)",
                   (user_id, website, username, encrypted_password))

    con.commit()
    con.close()


def get_password_entries(user_id):
    con = connection()
    cursor = con.cursor()
    cursor.execute(
        "SELECT id, website, username, password FROM user_data WHERE user_id = ?", (user_id,))

    results = cursor.fetchall()

    con.close()
    return results


def delete_password_entry(entry_id):
    conn = connection()
    cursor = conn.cursor()
    cursor.execute("DELETE FROM user_data WHERE id = ?", (entry_id,))
    conn.commit()
    conn.close()
