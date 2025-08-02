# AI help with GUI syntax and a little torubleshooting
import tkinter as tk
from tkinter import messagebox
import hashlib
import db
import user_dashboard
import secrets


def generate_salt():
    return secrets.token_hex(16)


def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode()).hexdigest()


def launch_login_screen():  # Main login screen, start the logic from here
    def login():
        username = username_entry.get().strip()
        password = password_entry.get().strip()

        if not username or not password:  # compulsory both fields should be filled
            messagebox.showwarning("Input Error", "Both fields are required.")
            return

        user_data = db.get_user(username)

        if user_data is None:  # ensure the input username exists
            # in case user doesn't exist, give option to register
            response = messagebox.askyesno(
                "User Not Found", "User doesn't exist. Would you like to register?")
            if response:
                open_register_window()
            return

        user_id = user_data[0]
        stored_hash = user_data[1]
        salt = user_data[2]

        input_hash = hashlib.sha256((salt + password).encode()
                                    ).hexdigest()  # hash the input password

        if input_hash == stored_hash:  # check password match
            messagebox.showinfo("Login Success", f"Welcome {username}!")
            root.destroy()  # close login window
            user_dashboard.open_dashboard(user_id, username)  # passon to the user_dashboard
        else:
            messagebox.showerror("Login Failed", "Incorrect password!")

    def open_register_window():  # register a new user
        register_window = tk.Toplevel(root)
        register_window.title("Register New User")
        register_window.geometry("300x250")

        tk.Label(register_window, text="Username").pack(pady=5)
        new_username = tk.Entry(register_window)
        new_username.pack()

        tk.Label(register_window, text="Password").pack(pady=5)
        new_password = tk.Entry(register_window, show="*")
        new_password.pack()

        tk.Label(register_window, text="Confirm Password").pack(pady=5)
        confirm_password = tk.Entry(register_window, show="*")
        confirm_password.pack()

        def handle_registration():
            u = new_username.get().strip()
            p1 = new_password.get().strip()
            p2 = confirm_password.get().strip()

            if not u or not p1 or not p2:
                messagebox.showwarning("Input Error", "All fields are required.")
                return

            if p1 != p2:
                messagebox.showerror("Password Mismatch", "Passwords do not match.")
                return

            salt = generate_salt()
            pass_hash = hash_password(p1, salt)

            try:
                db.create_user(u, pass_hash, salt)
                messagebox.showinfo("Success", "User registered successfully!")
                register_window.destroy()
            except Exception as e:
                messagebox.showerror("Error", f"Could not register user: {e}")

        tk.Button(register_window, text="Register", command=handle_registration).pack(pady=10)

    # GUI Initialization
    global root, username_entry, password_entry
    root = tk.Tk()
    root.title("Login - PassFort")
    root.geometry("300x200")

    tk.Label(root, text="Username").pack(pady=5)
    username_entry = tk.Entry(root)
    username_entry.pack()

    tk.Label(root, text="Password").pack(pady=5)
    password_entry = tk.Entry(root, show="*")
    password_entry.pack()

    tk.Button(root, text="Login", command=login).pack(pady=10)
    tk.Button(root, text="Register", command=open_register_window).pack()

    root.mainloop()
