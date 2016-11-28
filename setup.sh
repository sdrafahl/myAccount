

echo "Create New MYSQL USER: y,n"
read new
echo "Please Enter Either New User or Existing User"
read user
echo "Please Enter Either New Password or Existing Password"
read password
if ["$new" = "y"]; then
    echo "Creating New User at localhost"
    mysql -e "CREATE USER ${user}@localhost IDENTIFIED BY '${password}';"
fi
mysql -e -p"$password" CREATE DATABASE accountDB
mysql -e -p"$password" GRANT ALL PRIVILEGES ON ${user}.* TO '${user}'@'localhost'
mysql -e -p"$password" FLUSH PRIVILEGES;
mysql -u "$user" accountDB < layout.sql
# note database is accountDB , table ACCOUNTS and table TABLE_<ACCOUNT>


