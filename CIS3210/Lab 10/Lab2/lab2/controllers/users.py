import logging
import MySQLdb
import requests, json

from pylons import request, response, session, tmpl_context as c, url
from pylons.controllers.util import abort, redirect

from lab2.lib.base import BaseController, render

log = logging.getLogger(__name__)

class UsersController(BaseController):
	def index(self):
		return render("/index.mako")

	def API(self):
		API = "http://www.fantasyfootballnerd.com/service/"
		api_key = "dp8fs5kp88nm/"
		format = "json/"
		position = ""
		week = ""
		weekNum = ""

		if "service" in request.params and "rankingPos" in request.params:
			service_name = request.params["service"]
			position = request.params["rankingPos"]
			week = request.params["week"]
		elif "service" in request.params and "projectionPos" in request.params:
			service_name = request.params["service"]
			position = request.params["projectionPos"]
			week = request.params["week"]
		elif "service" in request.params and "week" in request.params:
			service_name = request.params["service"]
			weekNum = request.params["week"]

		url = API + service_name + format + api_key + position + week
		
		r = requests.get(url)
		req = r.json()		  
		Array = []
		number = 0;

		if "Rankings" in req:

			for x in req["Rankings"]:
				team = req["Rankings"][number]["team"]
				pName = req["Rankings"][number]["name"]
				points = req["Rankings"][number]["standard"]
				weekNum = req["Rankings"][number]["week"]
				position = req["Rankings"][number]["position"]
				number += 1
				stats = {"team": team, "name": pName, "points": points, "week": weekNum, "position": position}
				Array.append(stats)

			return json.dumps(Array)

		elif "Projections" in req:

			if "QB" in req["Position"]:
				for x in req["Projections"]:
					position = req["Projections"][number]["position"]
					team = req["Projections"][number]["team"]
					pName = req["Projections"][number]["displayName"]
					weekNum = req["Projections"][number]["week"]
					passAtt = req["Projections"][number]["passAtt"]
					passCmp = req["Projections"][number]["passCmp"]
					passYds = req["Projections"][number]["passYds"]
					passTD = req["Projections"][number]["passTD"]
					passInt = req["Projections"][number]["passInt"]
					rushYds = req["Projections"][number]["rushYds"]
					rushTD = req["Projections"][number]["rushTD"]
					number += 1
					stats = {"position": position, "team": team, "name": pName, "week": weekNum, 
						     "passAtt": passAtt, "passCmp": passCmp, "passTD": passTD, "passYds": passYds, "passInt": passInt,
							 "rushYds": rushYds, "rushTD": rushTD}
					Array.append(stats)

				return json.dumps(Array)

			elif "K" in req["Position"]:
				for x in req["Projections"]:
					position = req["Projections"][number]["position"]
					team = req["Projections"][number]["team"]
					pName = req["Projections"][number]["displayName"]
					weekNum = req["Projections"][number]["week"]
					fgAtt = req["Projections"][number]["fgAtt"]
					fg = req["Projections"][number]["fg"]
					xp = req["Projections"][number]["xp"]
					number += 1
					stats = {"position": position, "team": team, "name": pName, "week": weekNum, "fgAtt": fgAtt, "fg": fg, "xp": xp}
					Array.append(stats)	

				return json.dumps(Array)

			elif "DEF" in req["Position"]:
				for x in req["Projections"]:
					position = req["Projections"][number]["position"]
					pName = req["Projections"][number]["displayName"]
					weekNum = req["Projections"][number]["week"]
					defInt = req["Projections"][number]["defInt"]
					defFR = req["Projections"][number]["defFR"]
					defFF = req["Projections"][number]["defFF"]
					defSack = req["Projections"][number]["defSack"]
					defTD = req["Projections"][number]["defTD"]
					defRetTD = req["Projections"][number]["defRetTD"]
					defSafety = req["Projections"][number]["defSafety"]
					defPA = req["Projections"][number]["defPA"]
					defYdsAllowed = req["Projections"][number]["defYdsAllowed"]
					number += 1
					stats = {"position": position, "name": pName, "week": weekNum, "defInt": defInt, "defFR": defFR, "defFF": defFF,
							 "defSack": defSack, "defTD": defTD, "defRetTD": defRetTD, "defSafety": defSafety, "defPA": defPA, 
							 "defYdsAllowed": defYdsAllowed}
					Array.append(stats)	

				return json.dumps(Array)

			elif "WR" or "RB" or "TE" in req["Position"]:
				for x in req["Projections"]:
					position = req["Projections"][number]["position"]
					team = req["Projections"][number]["team"]
					pName = req["Projections"][number]["displayName"]
					weekNum = req["Projections"][number]["week"]
					receptions = req["Projections"][number]["receptions"]
					recYds = req["Projections"][number]["recYds"]
					recTD = req["Projections"][number]["recTD"]
					rushAtt = req["Projections"][number]["rushAtt"]
					rushYds = req["Projections"][number]["rushYds"]
					rushTD = req["Projections"][number]["rushTD"]
					number += 1
					stats = {"position": position, "team": team, "name": pName, "week": weekNum, 
							 "receptions": receptions, "recYds": recYds, "rushAtt": rushAtt, "recTD": recTD,
							 "rushYds": rushYds, "rushTD": rushTD}
					Array.append(stats)

				return json.dumps(Array)
				
		elif "Schedule" in req:
		    for x in req["Schedule"]:
			if req["Schedule"][number]["gameWeek"] == weekNum:
			    away = req["Schedule"][number]["awayTeam"]
			    home = req["Schedule"][number]["homeTeam"]
			    gameTime = req["Schedule"][number]["gameTimeET"]
			    gameDay = req["Schedule"][number]["gameDate"]
			    #print away + " " + home + " " + gameTime
			    stats = {"away": away, "home": home, "gameTime": gameTime, "gameDay": gameDay}    
			    Array.append(stats)
			number += 1
			
		    return json.dumps(Array)
			    