create or replace function p6() returns void as $$
	declare
		c1 cursor for select Vno, Vname, Vbalance from vendor;
		
		ven_Name TEXT;
		ven_Vno TEXT;
		fee NUMERIC(8,2);
		ven_Balance NUMERIC(8,2);

	begin
		open c1;
		loop
			fetch c1 into ven_Vno, ven_Name, ven_Balance;
			exit when not found;

			fee = 0.04 * ven_Balance;

			ven_Balance = ven_Balance - fee;

			update vendor set Vbalance =  ven_Balance where Vno = ven_Vno;

			raise notice 'Vendor Name: % | Fee Charged: % | Vendor Balance %', ven_Name, fee, ven_Balance;
			raise notice '----------------------------------------------';
		end loop;
		close c1;
	end
	
$$ language plpgsql;