create or replace function p4() returns void as $$
	declare
		c1 cursor for select customer.Account, Cname from customer;

		cxAccount TEXT;
		cxName TEXT;
		tAmount NUMERIC(8,2);
		ven_Name TEXT;
		
		numTransactions INT;

	begin
		open c1;
		loop
			fetch c1 into cxAccount, cxName;
			exit when not found;

			numTransactions :=(SELECT count(*) from transaction where transaction.account = cxAccount);

			if (numTransactions = 0) then
			    raise notice 'No Transactions';
			    raise notice '----------------------------------------------';
			
			elseif (numTransactions = 1) then
			    tAmount :=(SELECT Amount from transaction where transaction.account = cxAccount);
			    ven_Name :=(SELECT Vname from vendor, transaction where transaction.Vno = vendor.Vno and transaction.account = cxAccount );
			    raise notice 'Customer Account: % | Customer Name: % | Amount: % | Vendor Name: % ', cxAccount, cxName, tAmount, ven_Name;
			    raise notice '----------------------------------------------';

			elseif (numTransactions > 1) then
			    tAmount :=(SELECT Amount from transaction where transaction.account = cxAccount and T_Date = (SELECT MAX(T_Date) from transaction where transaction.account = cxAccount));
			    ven_Name :=(SELECT Vname from vendor, transaction 
					where transaction.Vno = vendor.Vno and transaction.account = cxAccount and T_Date = (SELECT MAX(T_Date) from transaction where transaction.account = cxAccount));
			    raise notice 'Customer Account: % | Customer Name: % | Amount: % | Vendor Name: % ', cxAccount, cxName, tAmount, ven_Name;
			    raise notice '----------------------------------------------';

			end if;
		end loop;
		close c1;
	end

$$ language plpgsql;