create or replace function p2(name TEXT) returns void as $$
	declare
		c1 cursor for select customer.Account, Cname, Province
		from vendor, transaction, customer
		where Vname = name and vendor.Vno = transaction.Vno and customer.Account = transaction.Account ;

		cAccount text;
		cName text;
		cProv text;

	begin
		open c1;
		loop
			fetch c1 into cAccount, cName, cProv;
			exit when not found;
			raise notice 'Customer Account: % | Customer Name: % | Province: %', cAccount, cName, cProv;
			raise notice '----------------------------------------------';
		end loop;
		close c1;
	end

$$ language plpgsql;