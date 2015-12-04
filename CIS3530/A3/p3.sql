create or replace function p3(aNum TEXT, name TEXT, cxProvince TEXT, balance NUMERIC(8,2), cxLimit INTEGER) returns void as $$
	declare
		c1 cursor for select * from customer;

		cxAccount TEXT;
		cxName TEXT;
		cxProv TEXT;
		cxBalance NUMERIC(8,2);
		cLimit INTEGER;

	begin
		INSERT INTO customer (Account, Cname, Province, Cbalance, Crlimit) VALUES (aNum, name, cxProvince, 0, cxLimit);

		open c1;
		loop
			fetch c1 into cxAccount, cxName, cxProv, cxBalance, cLimit;
			exit when not found;
			raise notice 'Customer Account: % | Customer Name: % | Province: % | Customer Balance: % | Customer Limit: %', cxAccount, cxName, cxProv, cxBalance, cLimit;
			raise notice '----------------------------------------------';
		end loop;
		close c1;
	end

$$ language plpgsql;