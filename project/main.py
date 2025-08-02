import db
import gui


def main():
    # Ensure database tables are created before anything else
    db.create_tables()

    # Launch the GUI login screen
    gui.launch_login_screen()


if __name__ == "__main__":
    main()
