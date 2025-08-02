# AI help with GUI syntax and a little torubleshooting
import tkinter as tk
from tkinter import messagebox, simpledialog
import db


def open_dashboard(user_id, username):  # this is what the user will see after a successfull login
    dashboard = tk.Tk()
    dashboard.title(f"{username}'s Password Vault")
    dashboard.geometry("650x400")

    # Header
    tk.Label(dashboard, text=f"Welcome, {username}!", font=("Arial", 14)).pack(pady=10)

    # Frame for Password Entries
    list_frame = tk.Frame(dashboard)
    list_frame.pack(fill="both", expand=True, padx=10)

    # Column Headers
    headers = ["ID", "Website", "Username", "Password", "Actions"]
    for col, header in enumerate(headers):
        tk.Label(list_frame, text=header, font=("Arial", 10, "bold")).grid(
            row=0, column=col, padx=5, pady=5)

    # Clear old rows and load entries
    def load_entries():
        for widget in list_frame.winfo_children()[len(headers):]:
            widget.destroy()

        entries = db.get_password_entries(user_id)

        for idx, entry in enumerate(entries, start=1):
            entry_id, website, uname, encrypted_pwd = entry

            tk.Label(list_frame, text=str(entry_id)).grid(row=idx, column=0, padx=5, pady=5)
            tk.Label(list_frame, text=website).grid(row=idx, column=1, padx=5, pady=5)
            tk.Label(list_frame, text=uname).grid(row=idx, column=2, padx=5, pady=5)
            tk.Label(list_frame, text="********").grid(row=idx, column=3, padx=5, pady=5)

            action_frame = tk.Frame(list_frame)
            action_frame.grid(row=idx, column=4, padx=5, pady=5)

            # Copy Button
            tk.Button(action_frame, text="Copy", width=6, command=lambda ep=encrypted_pwd,
                      uname=uname: copy_password(ep, uname)).pack(side="left", padx=2)

            # Delete Button
            tk.Button(action_frame, text="Delete", width=6,
                      command=lambda eid=entry_id: delete_entry(eid)).pack(side="left", padx=2)

    # Add Entry

    def add_entry():
        website = simpledialog.askstring("Website", "Enter website:")
        uname = simpledialog.askstring("Username", "Enter username/email:")
        pwd = simpledialog.askstring("Password", "Enter password:")

        if website and uname and pwd:
            db.add_password_entry(user_id, website.strip(), uname.strip(), pwd.strip())
            load_entries()
        else:
            messagebox.showwarning("Input Error", "All fields are required.")

    # Delete Entry
    def delete_entry(entry_id):
        confirm = messagebox.askyesno(
            "Confirm Delete", f"Are you sure you want to delete entry ID {entry_id}?")
        if confirm:
            db.delete_password_entry(entry_id)
            load_entries()

    # Copy Password to Clipboard
    def copy_password(encrypted_pwd, site_username):
        try:
            decrypted = db.decrypt_password(encrypted_pwd, site_username)
            dashboard.clipboard_clear()
            dashboard.clipboard_append(decrypted)
            dashboard.update()
            messagebox.showinfo("Copied", "Password copied to clipboard!")
        except Exception as e:
            print(f"Copy error: {e}")  # for debugging
        messagebox.showerror("Error", f"Failed to copy password: {e}")

    # Buttons
    button_frame = tk.Frame(dashboard)
    button_frame.pack(pady=10)

    tk.Button(button_frame, text="Add Entry", width=15,
              command=add_entry).grid(row=0, column=0, padx=5)
    tk.Button(button_frame, text="Refresh", width=15,
              command=load_entries).grid(row=0, column=1, padx=5)

    # Initial Load
    load_entries()

    dashboard.mainloop()
