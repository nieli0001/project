CREATE TABLE userInfo (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(100),
    userid VARCHAR(100),
    password VARCHAR(100),
    userage INT
);

CREATE TABLE bankInfo (
    id INT AUTO_INCREMENT PRIMARY KEY,
    bankName VARCHAR(100),
    bankNumber VARCHAR(100),
    bankBalance VARCHAR(100)
);
