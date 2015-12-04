create or replace function p8(tNum TEXT, vNum TEXT, aNum TEXT, newAmount NUMERIC(8,2)) returns void as $$
	declare
		c1 cursor for select Account, Cbalance, Vno, Vbalance from customer, vendor;
		c2 cursor for select Vno, Account, Amount from transaction;
		
		cxAccount TEXT;
		cxBalance NUMERIC(8,2);
		ven_Vno TEXT;
		ven_Vbalance NUMERIC(8,2);
		tVno TEXT;
		tAccount TEXT;
		tAmount NUMERIC(8,2);


	begin
		newDate := (SELECT(CURRENT_DATE));
		INSERT INTO transaction (Tno, Vno, Account, T_Date, Amount) VALUES (tNum, vNum, aNum, newDate, newAmount);

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