create or replace function p1(name TEXT) returns void as $$
	declare
		c1 cursor for select Vname, T_date, Amount
		from customer, transaction, vendor
		where Cname = name and customer.Account = transaction.Account and transaction.Vno = vendor.Vno;

		vName TEXT;
		tDate DATE;
		cAmount NUMERIC(8,2);

	begin
		open c1;
		loop
			fetch c1 into vName, tDate, cAmount;
			exit when not found;
			raise notice 'Vendor Name: % | Date: % | Amount: %', vName, tDate, cAmount;
			raise notice '----------------------------------------------';
		end loop;
		close c1;
	end

$$ language plpgsql;