create or replace function p7() returns void as $$
	declare
		c1 cursor for select Cname, Cbalance, Crlimit from customer;
		
		cxName TEXT;
		cxBalance NUMERIC(8,2);
		cxLimit INTEGER;
		fee NUMERIC(8,2);
		overage NUMERIC(8,2);

	begin
		open c1;
		loop
			fetch c1 into cxName, cxBalance, cxLimit;
			exit when not found;

			if (cxBalance > cxLimit) then
				overage := cxBalance - cxLimit;
				fee = 0.10 * overage;
				cxBalance = cxBalance + fee;

				update customer set Cbalance = cxBalance where Cname = cxName;

				raise notice 'Customer Name: % | New Balance: %', cxName, cxBalance;
				raise notice '----------------------------------------------';

			end if;

		end loop;
		close c1;
	end

$$ language plpgsql;