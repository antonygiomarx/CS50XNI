import datetime
import time

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import *

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    query = db.execute("SELECT symbol, shares FROM transactions WHERE user_id = :id", id=session["user_id"])

    basket = get_basket(query)

    portfolio = get_portfolio(basket)

    total_global = 0.0

    for i in range(len(portfolio)):
        for j in range(len(portfolio[i])):
            symbol = lookup(portfolio[i][j]["symbol"])
            portfolio[i][j].update({"price":symbol["price"]})
            portfolio[i][j].update({"total":symbol["price"] * portfolio[i][j]["shares"]})
            total_global = total_global + portfolio[i][j]["total"]

    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

    cash = cash[0]["cash"]

    cash = cash + total_global

    return render_template("index.html", portfolio=portfolio, cash=cash, total=total_global)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        symbol = lookup(request.form.get("symbol"))

        if symbol == None:
            return apology("invalid symbol, set a valid symbol", 400)

        shares = request.form.get("shares")

        try:
            shares = float(shares)

        except ValueError:
            return apology("Is not a number",  400)

        if request.form.get("shares") == None or shares < 0:
            return apology("Invalid number", 400)

        if is_whole(request.form.get("shares")) == False:
            return apology("must be a whole number", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        if cash[0]["cash"] - (symbol["price"] * shares) < 0:
            return apology("Cannot Afford", 400)
        else:
            db.execute("INSERT INTO transactions (symbol, user_id, at_price, time_date, shares) \
            VALUES (:symbol, :user_id, :at_price, :time_date, :shares)", \
            symbol = symbol["symbol"],
            user_id=session["user_id"],
            at_price=float(symbol["price"]),
            time_date=datetime.datetime.now().strftime("%d-%m-%y %H:%M"),
            shares=request.form.get("shares"))

            db.execute("UPDATE users SET cash = cash - :price WHERE id = :user_id", \
            price=float(symbol["price"]) * float(request.form.get("shares")), user_id=session["user_id"])

            remaining_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

            return render_template("bought.html", symbol=symbol["symbol"], price=float(symbol["price"]), value_of_holding=shares * float(symbol["price"]), cash=float(remaining_cash[0]["cash"]))

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT symbol, shares FROM transactions WHERE user_id = :id", id=session["user_id"])

    basket = get_basket(transactions)

    portfolio = get_portfolio(basket)

    return render_template("history.html", portfolio=portfolio)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

    if request.method == "POST":

        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("invalid ticker", 400)

        else:
            return render_template("quoted.html", symbol=quote["symbol"], price=usd(quote["price"]))

    else:
         return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    if request.method == "POST":

        user = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not user or not password or not confirmation:
            return apology("username, password, confirmation must be completed")
        elif not password == confirmation:
            return apology("passwords not match", 400)

        rows = db.execute("SELECT * FROM users WHERE username=:user", user=user)

        if len(rows) < 0:
            return apology("user already exists", 400)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", \
            username=user, hash = generate_password_hash(password))

        return redirect(url_for("index"))

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "GET":
        transactions = db.execute("SELECT symbol, shares FROM transactions WHERE user_id = :id",id=session["user_id"])
        basket = get_basket(transactions)
        return render_template("sell.html", list=basket)

    else:
        flash("Sold!")
        return redirect(url_for(index))


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
