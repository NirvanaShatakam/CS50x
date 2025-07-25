import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    transactions = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price price FROM transactions WHERE user_id = (?) GROUP BY symbol", user_id)
    cash_left = db.execute("SELECT cash FROM users WHERE id = (?)", user_id)

    cash = cash_left[0]["cash"]

    return render_template("index.html", database=transactions, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not shares or not shares.isdigit():
            return apology("Invalid number of shares")

        shares = int(shares)

        if not symbol:
            return apology("Missing Symbol")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("Does not Exist")
        if shares <= 0:
            return apology("Cannot buy Negative shares")

        cost = shares * float(stock["price"])

        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = (?)", user_id)

        show_cash = user_cash[0]["cash"]

        if show_cash < cost:
            return apology("Inadequate Funds")

        new_cash = show_cash - cost

        db.execute("UPDATE users SET cash = (?) WHERE id = (?)", new_cash, user_id)

        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?,?,?,?,?)",
                   user_id, stock["symbol"], shares, stock["price"], date)

        flash("SUCCESS!")

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing Symbol")
        stock = lookup(symbol.upper())

        if stock == None:
            return apology("Does not Exist")
        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Username Missing")
        if not password:
            return apology("Password Missing")
        if not confirmation:
            return apology("Confirm the password please")
        if password != confirmation:
            return apology("Passwords don't match")

        pass_hash = generate_password_hash(confirmation)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, pass_hash)
        except:
            return apology("Username Exists")
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        symbol = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = (?) GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbol])
    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("Missing Symbol")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("Does not Exist")
        if shares <= 0:
            return apology("Cannot buy Negative shares")

        cost = shares * float(stock["price"])

        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = (?)", user_id)

        show_cash = user_cash[0]["cash"]

        final_shares = db.execute(
            "SELECT SUM(shares) as shares FROM transactions WHERE user_id = (?) AND symbol = (?)", user_id, symbol)
        shares_new = final_shares[0]["shares"]

        if shares > shares_new:
            return apology("Not enough Shares")

        new_cash = show_cash + cost

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?,?,?,?,?)",
                   user_id, stock["symbol"], (- 1) * shares, stock["price"], date)

        flash("SUCCESS!")

        return redirect("/")


@app.route("/add", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add Cash."""
    if request.method == "GET":
        return render_template("add.html")
    else:
        cash = request.form.get("cash")

        if not cash:
            return apology("Add Valid Amount")

        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = (?)", user_id)

        show_cash = user_cash[0]["cash"]

        new_cash = show_cash + float(cash)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        return redirect("/")
