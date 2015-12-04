CREATE TABLE vendor(
	Vno TEXT PRIMARY KEY NOT NULL,
	Vname TEXT NOT NULL,
	City TEXT NOT NULL,
	Vbalance NUMERIC(8,2) NOT NULL
);

CREATE TABLE customer(
	Account TEXT PRIMARY KEY NOT NULL,
	Cname TEXT NOT NULL,
	Province TEXT NOT NULL,
	Cbalance NUMERIC(8,2) NOT NULL,
	Crlimit INT NOT NULL
);

CREATE TABLE transaction(
	Tno TEXT PRIMARY KEY NOT NULL,
	Vno TEXT NOT NULL,
	Account TEXT NOT NULL,
	T_Date DATE NOT NULL,
	Amount NUMERIC(8,2) NOT NULL
);

INSERT INTO vendor (Vno, Vname, City, Vbalance) VALUES('V1', 'Sears', 'Toronto', 200.00);
INSERT INTO vendor (Vno, Vname, City, Vbalance) VALUES('V2', 'WalMart', 'Waterloo', 671.05);
INSERT INTO vendor (Vno, Vname, City, Vbalance) VALUES('V3', 'Esso', 'Windsor', 0.00);
INSERT INTO vendor (Vno, Vname, City, Vbalance) VALUES('V4', 'Esso', 'Waterloo', 225.00);

INSERT INTO customer (Account, Cname, Province, Cbalance, Crlimit) VALUES('A1', 'Smith', 'ONT', 2515.00, 2000);
INSERT INTO customer (Account, Cname, Province, Cbalance, Crlimit) VALUES('A2', 'Jones', 'BC', 2014.00, 2500);
INSERT INTO customer (Account, Cname, Province, Cbalance, Crlimit) VALUES('A3', 'Doc', 'ONT', 150.00, 1000);

INSERT INTO transaction (Tno, Vno, Account, T_Date, Amount) VALUES('T1', 'V2', 'A1' ,'2014-07-15', 1325.00);
INSERT INTO transaction (Tno, Vno, Account, T_Date, Amount) VALUES('T2', 'V2', 'A3' ,'2013-12-16', 1900.00);
INSERT INTO transaction (Tno, Vno, Account, T_Date, Amount) VALUES('T3', 'V3', 'A1' ,'2014-09-01', 2500.00);
INSERT INTO transaction (Tno, Vno, Account, T_Date, Amount) VALUES('T4', 'V4', 'A2' ,'2013-03-20', 1613.00);
INSERT INTO transaction (Tno, Vno, Account, T_Date, Amount) VALUES('T5', 'V4', 'A3' ,'2014-07-31', 3312.00);

