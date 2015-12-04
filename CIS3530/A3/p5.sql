create or replace function p5() returns void as $$
	declare

		c1 cursor for select Vno, Vname, Vbalance from vendor;

		ven_Vno TEXT;
		ven_Balance NUMERIC(8,2);
		ven_Name TEXT;
		tAmount NUMERIC(8,2);

		c2 cursor for select Amount from transaction where Vno = ven_Vno;

	begin
		open c1;
		loop
			fetch c1 into ven_Vno, ven_Name, ven_Balance;
			exit when not found;

			open c2;
			loop
			    fetch c2 into tAmount;
			    exit when not found;

			    ven_Balance := ven_Balance + tAmount;
			    
			end loop;
			close c2;

			update vendor set Vbalance = ven_Balance where Vno = ven_Vno;

		end loop;
		close c1;

		open c1;
		loop
		    fetch c1 into ven_Vno, ven_Name, ven_Balance;
		    exit when not found;

		    raise notice 'Vendor Number: % | Vendor Name: % | Vendor Balance %', ven_Vno, ven_Name, ven_Balance;
		    raise notice '----------------------------------------------';

		end loop;
		close c1;
	end

$$ language plpgsql;