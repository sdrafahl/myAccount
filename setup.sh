echo "Please Enter Your MySQL Username or if You Dont Have a Username Please Reread README.md"
read user
mysql -p -u "$user" accountDB < layout.dump


# note database is accountDB , user is shane, table per user