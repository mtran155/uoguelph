#!/usr/bin/python3
# -*- coding: utf-8 -*-

#####################################################################################
#										    #
#  xvcf.py  - GUI application that uses the utilities in vcutil through vcftool     #
#                                                                                   #
#  Author: Michael Tran #0524704                                                    #
#  Date Created: March 1, 2014                                                      #
#  Contact: mtran04@uoguelph.ca                                                     #
#							                            #
#####################################################################################

# All credit goes to http://code.activestate.com/recipes/52266-multilistbox-tkinter-widget/ for the multilist box widget

from tkinter import *
import tkinter.messagebox
from tkinter.filedialog import askopenfilename
from tkinter.filedialog import asksaveasfilename
from GMapData import *
import Vcf
import re
import mysql.connector
import sys
from mysql.connector import errorcode


root = Tk()
textframe = Frame(root, bg = 'grey')
text = Text(textframe, height = 10, width = 120, bg = 'white')
cardList = []
backupList = []
newCard = 0
addProp = 0
queryOpen = 0
cnx = ""
cursor = ""
saveDisabled = 0

def closeWindow(e):
	e.destroy()

def insertText(line):
	text.insert(END, line)
	text.yview(END)

########### PANEL VIEW CLASSES ####################
class MultiListbox(Frame):
	def __init__(self, master, lists):
		Frame.__init__(self,master)
		self.lists = []
		for l,w in lists:
			frame = Frame(self)
			frame.pack(side=LEFT, expand=YES, fill=BOTH)
			Label(frame, text=l, borderwidth=1, relief=GROOVE).pack(fill=X)
			lb = Listbox(frame, selectmode = EXTENDED, height = 8, width=w, borderwidth=0, selectborderwidth=0, 
				relief=FLAT, exportselection=FALSE)
			lb.pack(expand=YES, fill=BOTH)
			self.lists.append(lb)
			lb.bind('<B1-Motion>', lambda e, s=self: s._select(e.y))
			lb.bind('<Button-1>', lambda e, s=self: s._select(e.y))
			lb.bind('<Leave>', lambda e: 'break')
			lb.bind('<B2-Motion>', lambda e, s=self: s._b2motion(e.x, e.y))
			lb.bind('<Button-2>', lambda e, s=self: s._button2(e.x, e.y))
		frame = Frame(self)
		frame.pack(side=LEFT, fill=Y)
		Label(frame, borderwidth=1, relief=GROOVE).pack(fill=X)
		sb = Scrollbar(frame, orient=VERTICAL, command = self._scroll)
		sb.pack(expand=YES, fill=Y)
		self.lists[0]['yscrollcommand']=sb.set

	def _select(self, y):
	   	row = self.lists[0].nearest(y)
	   	self.selection_clear(0, END)
	   	self.selection_set(row)
	   	updateCardView()
	   	return 'break'
	
	def _button2(self, x, y):
		for l in self.lists: l.scan_mark(x, y)
		return 'break'

	def _b2motion(self, x, y):
		for l in self.lists: l.scan_dragto(x, y)
		return 'break'

	def _scroll(self, *args):
		for l in self.lists:
		    l.yview(*args)

	def curselection(self):
		return self.lists[0].curselection()

	def delete(self, first, last=None):
		for l in self.lists:
		    l.delete(first, last)

	def get(self, first, last=None):
		result = []
		for l in self.lists:
		    result.append(l.get(first,last))
		if last: return map(None, *result)
		return result
		    
	def index(self, index):
		self.lists[0].index(index)

	def insert(self, index, *elements):
		for e in elements:
		    i = 0
		    for l in self.lists:
		    	l.insert(index, e[i])
		    	i = i + 1

	def size(self):
		return self.lists[0].size()

	def see(self, index):
		for l in self.lists:
		    l.see(index)

	def selection_anchor(self, index):
		for l in self.lists:
		    l.selection_anchor(index)

	def selection_clear(self, first, last=None):
		for l in self.lists:
		    l.selection_clear(first, last)

	def selection_includes(self, index):
	   	return self.lists[0].selection_includes(index)

	def selection_set(self, first, last=None):
	   	for l in self.lists:
	   		l.selection_set(first, last)

class MultiListbox2(Frame):
	def __init__(self, master, lists):
		Frame.__init__(self,master)
		self.lists = []
		for l,w in lists:
			frame = Frame(self)
			frame.pack(side=LEFT, expand=YES, fill=BOTH)
			Label(frame, text=l, borderwidth=1, relief=GROOVE).pack(fill=X)
			lb = Listbox(frame, selectmode = SINGLE, height = 8, width=w, borderwidth=0, selectborderwidth=0, 
				relief=FLAT, exportselection=FALSE)
			lb.pack(expand=YES, fill=BOTH)
			self.lists.append(lb)
			lb.bind('<B1-Motion>', lambda e, s=self: s._select(e.y))
			lb.bind('<Button-1>', lambda e, s=self: s._select(e.y))
			lb.bind('<Leave>', lambda e: 'break')
			lb.bind('<B2-Motion>', lambda e, s=self: s._b2motion(e.x, e.y))
			lb.bind('<Button-2>', lambda e, s=self: s._button2(e.x, e.y))
		frame = Frame(self)
		frame.pack(side=LEFT, fill=Y)
		Label(frame, borderwidth=1, relief=GROOVE).pack(fill=X)
		sb = Scrollbar(frame, orient=VERTICAL, command = self._scroll)
		sb.pack(expand=YES, fill=Y)
		sbH = Scrollbar(frame, orient = HORIZONTAL, command = self.horizontalScroll)
		sbH.pack(expand = YES, fill = X)
		self.lists[0]['yscrollcommand']=sb.set

	def _select(self, y):
	   	row = self.lists[0].nearest(y)
	   	self.selection_clear(0, END)
	   	self.selection_set(row)
	   	return 'break'
	
	def _button2(self, x, y):
		for l in self.lists: l.scan_mark(x, y)
		return 'break'

	def _b2motion(self, x, y):
		for l in self.lists: l.scan_dragto(x, y)
		return 'break'

	def _scroll(self, *args):
		for l in self.lists:
		    l.yview(*args)
		return 'break'

	def horizontalScroll(self, *args):
		for l in self.lists:
			l.xview(*args)
		return 'break'

	def curselection(self):
		return self.lists[0].curselection()

	def delete(self, first, last=None):
		for l in self.lists:
		    l.delete(first, last)

	def get(self, first, last=None):
		result = []
		for l in self.lists:
		    result.append(l.get(first,last))
		if last: return map(None, *result)
		return result
		    
	def index(self, index):
		self.lists[0].index(index)

	def insert(self, index, *elements):
		for e in elements:
		    i = 0
		    for l in self.lists:
		    	l.insert(index, e[i])
		    	i = i + 1

	def size(self):
		return self.lists[0].size()

	def see(self, index):
		for l in self.lists:
		    l.see(index)

	def selection_anchor(self, index):
		for l in self.lists:
		    l.selection_anchor(index)

	def selection_clear(self, first, last=None):
		for l in self.lists:
		    l.selection_clear(first, last)

	def selection_includes(self, index):
	   	return self.lists[0].selection_includes(index)

	def selection_set(self, first, last=None):
	   	for l in self.lists:
	   		l.selection_set(first, last)

mlb = MultiListbox(root, (('Card #', 1), ('Name', 35), ('Region', 10), ('Country', 25), ('# ADR', 2), ('# TEL', 2), ('Flags', 20)))
mlb2 = MultiListbox2(root,(('Name', 10), ('Type Parameter', 15), ('Value Parameter', 15), ('Property Value', 100)))

########### GUI PANELS ############################
def fileDisplay():
	frame = Frame()
	labelfont = ('bold', 10)
	label = Label(frame, text = "File View", bg = 'grey', font = labelfont)
	label.pack(anchor = W, fill = X)
	frame.pack(expand = YES, fill = BOTH)

def card_Display():
	frame = Frame(bg = 'grey')
	labelfont = ('bold', 10)
	label = Label(frame, text = "Card View", bg = 'grey', font = labelfont)
	label.pack(anchor = W, fill = X)
	frame.pack(expand = YES, fill = BOTH)

def logDisplay():
	Label(textframe, text = "Log", bg = 'grey').pack(anchor = W, fill = X)
	scroll = Scrollbar(textframe)
	button = Button(textframe, text = "Clear", command = clearText)
	button.pack(side = BOTTOM)
	text.configure(yscrollcommand = scroll.set)
	text.pack(side = LEFT)
	scroll.pack(side = RIGHT, fill = Y)
	textframe.pack(side = BOTTOM, expand = YES)

########### GUI PANEL BUTTONS #####################
def fileButtons():
	buttonFrame = Frame(bg = 'grey')
	button1 = Button(buttonFrame, text = "Map Selected", command = mapSelect)
	button2 = Button(buttonFrame, text = "Reset Map", command = resetMap)
	button3 = Button(buttonFrame, text = "Browse Selected", command = browseSelect)
	button1.pack(side = LEFT, pady = 5)
	button2.pack(side = LEFT)
	button3.pack(side = LEFT)
	buttonFrame.pack()
	buttonFrame2 = Frame(bg = 'grey')
	button4 = Button(buttonFrame2, text = "Delete Selected", command = deleteSelected)
	button5 = Button(buttonFrame2, text = "Add Card", command = addCard)
	button4.pack(side = LEFT, pady = 5)
	button5.pack(side = LEFT)
	buttonFrame2.pack()

def cardButtons():
	buttonFrame = Frame(bg='grey')
	button1 = Button(buttonFrame, text = "Up", command = upButton)
	button2 = Button(buttonFrame, text = "Down", command = downButton)
	button3 = Button(buttonFrame, text = "Add Property", command = addProp)
	button4 = Button(buttonFrame, text = "Delete Property", command = deleteProp)	
	button1.pack(side = LEFT, pady = 5)
	button2.pack(side = LEFT)
	button3.pack(side = LEFT)
	button4.pack(side = LEFT)	
	buttonFrame.pack()
	buttonFrame2 = Frame(bg='grey')
	button5 = Button(buttonFrame2, text = "Commit", command = commitButton)
	button6 = Button(buttonFrame2, text = "Revert", command = revertButton)
	button5.pack(side = LEFT, pady = 5)
	button6.pack(side = LEFT)
	buttonFrame2.pack()

########### FILE BUTTON ACTIONS ###################
def mapSelect():
	cardSelect = mlb.curselection()
	geoFlag = 0
	photoFlag = 0
	if len(cardSelect) != 0:
		cardNumber = int(cardSelect[0])
		for i in range(0, len(cardList[cardNumber])):
			if cardList[cardNumber][i][0] == "GEO":
				if geoFlag == 0:
					geo = cardList[cardNumber][i][3]
					geoFlag = 1
			if cardList[cardNumber][i][0] == "PHOTO":
				photo = cardList[cardNumber][i][3]
				photoFlag = 1
			if cardList[cardNumber][i][0] == "ADR":
				address = cardList[cardNumber][i][3]

		if photoFlag == 1:
			if "http://" in photo:
				photoFlag = 2
			else:
				insertText("Invalid Photo property (in wrong format)\n")

		if geoFlag == 1:
			if len(geo) == 0:
				if photoFlag == 2:
					launchBrowser(photo)
					insertText("Valid Photo but invalid GEO\n")
					return
				insertText("Invalid GEO property\n")
				return
			if geo == None:
				if photoFlag == 2:
					launchBrowser(photo)
					insertText("Valid Photo but invalid GEO\n")
					return
				insertText("Invalid GEO property\n")
				return
			print(geo)
			if "," in geo:
				splitGeo = geo.split(",")
				lat = float(splitGeo[0])
				lon = float(splitGeo[1])
			elif ";" in geo:
				splitGeo = geo.split(";")
				lat = float(splitGeo[0])
				lon = float(splitGeo[1])
			else:
				insertText("Invalid GEO property\n")
				return
			gmd = GMapData("Google Map", "Location", [lat,lon], 14)
			gmd.addPoint( [lat,lon], photo, address)
			gmd.addOverlay( 0, 1 ,3 )
			gmd.serve( "public_html/index.html" )
			launchBrowser( "http://localhost:44704" )
		else:
			insertText("No GEO property found\n")

def resetMap():
	insertText( "RESET MAP NOT IMPLEMENTED\n" )

def browseSelect():
	cardSelect = mlb.curselection()
	urlFlag = 0
	if len(cardSelect) != 0:
		cardNumber = int(cardSelect[0])
		for i in range(0, len(cardList[cardNumber])):
			if cardList[cardNumber][i][0] == "URL":
				if urlFlag == 0:
					url = cardList[cardNumber][i][3]
					urlFlag = 1

		if urlFlag == 1:
			if len(url) == 0:
				insertText("Invalid URL property\n")
			elif url == None:
				insertText("Invalid URL property\n")
			else:
				launchBrowser(url)
		else:
			insertText("No URL property found\n")

def deleteSelected():
	def deleteCard():
		cardSelect = mlb.curselection()
		if len(cardSelect) != 0:
		    cardNumber = int (cardSelect[0])
		    del cardList[cardNumber]
		top.destroy()
		updateFileView()
		clearCardView()

	if len(cardList) > 1:
		top = Toplevel()
		top.title("Confirm")
		top.geometry('420x100+500+360')
		top.bind('<Escape>', lambda e: closeWindow(top))
		msg = Message(top, text = "Are you sure want to delete the selected number of card(s)?", width = 300)
		msg.pack()
		button = Button(top, text = "OK", command = deleteCard)
		button2 = Button(top, text = "Cancel", command = top.destroy)
		button.pack(side = LEFT, expand = YES)
		button2.pack(side = LEFT, expand = YES)
	if len(cardList) == 1:
		top = Toplevel()
		top.title("Error")
		top.geometry('220x100+500+360')
		top.bind('<Escape>', lambda e: closeWindow(top))
		msg = Message(top, text = "Deleting Last card not allowed!", width = 200, fg ='red', font = 'bold')
		msg.pack()
		button = Button(top, text = "Cancel", command = top.destroy)
		button.pack(side = LEFT, expand = YES)

def addCard():
	global newCard
	if len(cardList) > 0:
		tempCard = [('N', '', '', ''), ('FN', '', '', '')]
		cardList.insert(len(cardList), tempCard)
		newCard = 1
		clearCardView()
		for i in range(len(tempCard)):
			propName = ""
			parVal = ""
			parType = ""
			value = ""
			propName = tempCard[i][0]
			parType = tempCard[i][1]
			parVal = tempCard[i][2]
			value = tempCard[i][3]
			mlb2.insert(END,(propName, parType, parVal, value))	
	updateFileView()
	mlb.selection_set(END)
	mlb.see(END)

########### CARD BUTTON ACTIONS ###################
def upButton():
	if len(cardList) != 0:
		propUp = 0
		cardSelect = mlb.curselection()
		if len(cardSelect) != 0:
		    cardNumber = int (cardSelect[0])
		    cardProp = mlb2.curselection()
		    if len(cardProp) != 0:
			    propUp = int (cardProp[0])
			    tempProp = cardList[cardNumber].pop(propUp)
			    propUp -= 1
			    cardList[cardNumber].insert(propUp,tempProp)
			    updateCardView()
		    if propUp > -1:
			    mlb2.selection_set(propUp)

def downButton():
	if len(cardList) != 0:
		propUp = 0
		cardSelect = mlb.curselection()
		if len(cardSelect) != 0:
			cardNumber = int (cardSelect[0])
			cardProp = mlb2.curselection()
			if len(cardProp) != 0:
				propUp = int (cardProp[0])
				tempProp = cardList[cardNumber].pop(propUp)
				propUp += 1
				cardList[cardNumber].insert(propUp,tempProp)
				updateCardView()
			if propUp > -1:
				mlb2.selection_set(propUp)
				
def addProp():
	def newProp():
		global addProp
		addProp = 1
		cardSelect = mlb.curselection()
		if len(cardSelect) != 0:
		    cardNumber = int (cardSelect[0])
		    propName = variable.get()
		    if propName != "OTHER":
			    parType = e.get()
			    parVal = e2.get()
			    value = e3.get()
			    tempCard = [(propName,parType,parVal,value)]
			    cardList[cardNumber].extend(tempCard)
		    else:
			    parType = ""
			    parVal = ""
			    value = e3.get()
			    tempCard = [(propName,parType,parVal,value)]
			    cardList[cardNumber].extend(tempCard)
		    updateFileView()
		    mlb.selection_set(cardNumber)
		    updateCardView()
		    top.destroy()
		else:
		    top.destroy()

	if len(cardList) != 0:
		top = Toplevel()
		top.title("Add Properties")
		top.geometry('300x150+500+360')
		top.bind('<Escape>', lambda e: closeWindow(top))
		variable = StringVar(top)
		variable.set("NICKNAME")
		w = OptionMenu(top, variable, "NICKNAME", "PHOTO", "BDAY", "ADR", "TEL", "EMAIL", "GEO", "TITLE", "ORG", 
			"NOTE", "UID", "URL", "OTHER")
		w.pack()

		topFrame = Frame(top)
		Label(topFrame, text = "PARTYPE:").pack(side = LEFT)
		e = Entry(topFrame)
		e.pack(side = LEFT,expand = YES )
		topFrame.pack(expand = YES)

		topFrame2 = Frame(top)
		Label(topFrame2, text = "PARVAL:").pack(side = LEFT)
		e2 = Entry(topFrame2)
		e2.pack(side = LEFT,expand = YES)
		topFrame2.pack(expand = YES)

		topFrame3 = Frame(top)
		Label(topFrame3, text = "VALUE:").pack(side = LEFT)
		e3 = Entry(topFrame3)
		e3.pack(side = LEFT,expand = YES)
		topFrame3.pack(expand = YES)

		topFrame4 = Frame(top)
		Button(topFrame4, text = "OK", command = newProp).pack(side = LEFT, expand = YES)
		Button(topFrame4, text = "Cancel", command = top.destroy).pack(side = LEFT, expand = YES)
		topFrame4.pack(expand = YES)

def deleteProp():
	if len(cardList) != 0:
		global delProp
		delProp = 1
		cardSelect = mlb.curselection()
		if len(cardSelect) !=0:
		    cardNumber = int (cardSelect[0])
		    cardProp = mlb2.curselection()
		    if len(cardProp) != 0:
			    propDel = int (cardProp[0])
			    del cardList[cardNumber][propDel]
			    updateCardView()
		    else:
			    top = Toplevel()
			    top.title("Error")
			    top.geometry('220x100+500+360')
			    top.bind('<Escape>', lambda e: closeWindow(top))
			    msg = Message(top, text = "Please select a property to delete", width = 300)
			    msg.pack()
			    button2 = Button(top, text = "Cancel", command = top.destroy)
			    button2.pack(side = LEFT, expand = YES)

def commitButton():
	if len(cardList) != 0:
		insertText("COMMIT BUTTON NOT IMPLEMENTED\n")

def revertButton():
	if len(cardList) != 0:
		insertText("REVERT BUTTON NOT IMPLEMENTED\n")

########### LOG BUTTON ACTIONS ####################
def clearText():
	text.delete(0.0, END)

########### FILE MENU BUTTONS #####################
def openButton():
	global backupList
	global saveDisabled
	saveDisabled = 0
	if(os.path.exists("output.txt")):
		os.remove("output.txt")

	filename = askopenfilename(filetypes = [("All Files", "*.*"), ("Vcard Files", "*.vcf")])
	tempCard = []

	if filename == "":
		return
	else:
		status = Vcf.readFile(filename)
		if status[0] == 'OK':
			if status[2] == 0:
				top = Toplevel()
				top.title("Error")
				top.geometry('250x100+500+360')
				top.bind('<Escape>', lambda e: closeWindow(top))
				msg = Message(top, text = 'No Cards found in file', width = 200)
				msg.pack(expand = YES)
				button = Button(top, text = "Cancel", command = top.destroy)
				button.pack()
				noCardString = "File " + filename + " opened successfully but has no Vcards\n"
				insertText(noCardString)
			else:
				info = "INFO:\n" + str(status[1])
				insertText(info)
				root.title(filename)
				if cardList != []:
					del cardList[:]
				for i in range(status[2]):
					tempCard = Vcf.getCard()
					cardList.append(tempCard)
					backupList.append(tempCard)
				updateFileView()
				mlb.selection_set(0)
				updateCardView()
				
		else:
			fileError = "Error reading file " + filename + " with the following errors " + str(status)
			insertText(fileError)

def appendButton():
	if len(cardList) != 0:
		filename = askopenfilename(filetypes = [("All Files", "*.*"), ("Vcard Files", "*.vcf")])
		tempCard = []
		
		if filename == "":
			return
		else:
			status = Vcf.readFile(filename)
			if status[0] == 'OK':
				if status[2] == 0:
					top = Toplevel()
					top.title("Error")
					top.geometry('250x100+500+360')
					top.bind('<Escape>', lambda e: closeWindow(top))
					msg = Message(top, text = 'No Cards found in file', width = 200)
					msg.pack(expand = YES)
					button = Button(top, text = "Cancel", command = top.destroy)
					button.pack()
					noCardString = "File " + filename + " opened successfully but has no Vcards\n"
					insertText(noCardString)
				else:
					for i in range(status[2]):
						tempCard = Vcf.getCard()
						cardList.append(tempCard)
						backupList.append(tempCard)
					updateFileView()
					mlb.selection_set(0)
					updateCardView()
				
			else:
				fileError = "Error reading file " + filename + " with the following errors " + str(status)
				insertText(fileError)
				
def saveButton():
	if saveDisabled == 0:
		insertText("SAVE NOT IMPLEMENTED\n")

def saveAsButton():
	filename = asksaveasfilename(filetypes = [("All Files", "*.*"), ("Vcard Files", "*.vcf")])
	root.title(filename)
	insertText("SAVE AS NOT FULLY IMPLEMENTED\n")

def quitProg():
	global cursor
	global cnx
	if(os.path.exists("output.txt")):
		os.remove("output.txt")
	killServers()
	root.quit()

def confirmQuit():
	top = Toplevel()
	top.title('Confirm')
	top.geometry('250x100+500+360')
	top.bind('<Escape>', lambda e: closeWindow(top))
	msg = Message(top, text = 'Are you sure you want to quit?', width = 200)
	msg.pack(fill = X, expand = YES)
	button = Button(top, text = 'Yes', command = quitProg)
	button.pack(side = LEFT, expand = YES)
	button2 = Button(top, text = 'No', command = top.destroy)
	button2.pack(side = LEFT, expand = YES)

########### ORGANIZE MENU BUTTONS #################
def sortButton():
	if len(cardList) != 0:
		insertText("SORT NOT IMPLEMENTED\n")

def canonButton():
	if len(cardList) != 0:
		insertText("CANON NOT IMPLEMENTED\n")

def selectButton():
	if len(cardList) != 0:
		top = Toplevel()
		top.title("Select Properties")
		top.geometry('220x100+500+360')
		top.bind('<Escape>', lambda e: closeWindow(top))
		CheckVar1 = IntVar()
		CheckVar2 = IntVar()
		CheckVar3 = IntVar()
		checkbox1 = Checkbutton(top, text = "Photos", variable = CheckVar1,  width = 50)
		checkbox2 = Checkbutton(top, text = "URLs", variable = CheckVar2,  width = 50)
		checkbox3 = Checkbutton(top, text = "Locations", variable = CheckVar3,  width = 50)
		checkbox1.pack()
		checkbox2.pack()
		checkbox3.pack()
		button = Button(top, text = "OK", command = top.destroy)
		button2 = Button(top, text = "Cancel", command = top.destroy)
		button.pack(side = LEFT, expand = YES)
		button2.pack(side = LEFT, expand = YES)
		insertText("SELECT NOT IMPLEMENTED\n")

def undoButton():
	if len(cardList) != 0:
		insertText("UNDO NOT IMPLEMENTED\n")

########### DATABASE MENU BUTTONS #################
def storeAll():
	global cnx
	global cursor

	if len(cardList) != 0:
		for i in range(len(cardList)):
			numFN = 0
			numNick = 0
			numPhoto = 0
			numBday = 0
			numAdr = 0
			numLabel = 0
			numTel = 0
			numEmail = 0
			numGeo = 0
			numTitle = 0
			numOrg = 0
			numNote = 0
			numUid = 0
			numUrl = 0
			numOther = 0

			for j in range(0, len(cardList[i])):
				if cardList[i][j][0] == "N":
					name = cardList[i][j][3]
					query = "INSERT INTO NAME (name) VALUES ('%s');" % name
					cursor.execute(query)
					cnx.commit()
				elif cardList[i][j][0] != "N":
					if cardList[i][j][0] == "FN":
						numFN += 1
						value = numFN
					if cardList[i][j][0] == "NICKNAME":
						numNick += 1
						value = numNick
					if cardList[i][j][0] == "PHOTO":
						numPhoto += 1
						value = numPhoto
					if cardList[i][j][0] == "BDAY":
						numBday += 1
						value = numBday
					if cardList[i][j][0] == "ADR":
						numAdr += 1
						value = numAdr
					if cardList[i][j][0] == "LABEL":
						numLabel += 1
						value = numLabel
					if cardList[i][j][0] == "TEL":
						numTel += 1
						value = numTel
					if cardList[i][j][0] == "EMAIL":
						numEmail += 1
						value = numEmail
					if cardList[i][j][0] == "GEO":
						numGeo += 1
						value = numGeo
					if cardList[i][j][0] == "TITLE":
						numTitle += 1
						value = numTitle
					if cardList[i][j][0] == "ORG":
						numOrg += 1
						value = numOrg
					if cardList[i][j][0] == "NOTE":
						numNote += 1
						value = numNote
					if cardList[i][j][0] == "UID":
						numUid += 1
						value = numUid
					if cardList[i][j][0] == "URL":
						numUrl += 1
						value = numUrl
					if cardList[i][j][0] == "OTHER":
						numOther += 1
						value = numOther

					query = "INSERT INTO PROPERTY (name_id, pname, pinst, partype, parval, value) VALUES (%d, '%s', %d, '%s', '%s','%s');" % ((i+1), cardList[i][j][0], value ,cardList[i][j][1], cardList[i][j][2], cardList[i][j][3])
					cursor.execute(query)
					cnx.commit()

def storeSelected():
	global cnx
	global cursor

	if len(cardList) != 0:
		cardSelect = mlb.curselection()
		cardNumber = int (cardSelect[0])
		numFN = 0
		numNick = 0
		numPhoto = 0
		numBday = 0
		numAdr = 0
		numLabel = 0
		numTel = 0
		numEmail = 0
		numGeo = 0
		numTitle = 0
		numOrg = 0
		numNote = 0
		numUid = 0
		numUrl = 0
		numOther = 0
		for i in range(0, len(cardList[cardNumber])):
			if cardList[cardNumber][i][0] == "N":
				name = cardList[cardNumber][i][3]
				query = "INSERT INTO NAME (name) VALUES (\'" + name + "\');"
				cursor.execute(query)
				cnx.commit()
			elif cardList[cardNumber][i][0] != "N":
				if cardList[cardNumber][i][0] == "FN":
					numFN += 1
					value = numFN
				if cardList[cardNumber][i][0] == "NICKNAME":
					numNick += 1
					value = numNick
				if cardList[cardNumber][i][0] == "PHOTO":
					numPhoto += 1
					value = numPhoto
				if cardList[cardNumber][i][0] == "BDAY":
					numBday += 1
					value = numBday
				if cardList[cardNumber][i][0] == "ADR":
					numAdr += 1
					value = numAdr
				if cardList[cardNumber][i][0] == "LABEL":
					numLabel += 1
					value = numLabel
				if cardList[cardNumber][i][0] == "TEL":
					numTel += 1
					value = numTel
				if cardList[cardNumber][i][0] == "EMAIL":
					numEmail += 1
					value = numEmail
				if cardList[cardNumber][i][0] == "GEO":
					numGeo += 1
					value = numGeo
				if cardList[cardNumber][i][0] == "TITLE":
					numTitle += 1
					value = numTitle
				if cardList[cardNumber][i][0] == "ORG":
					numOrg += 1
					value = numOrg
				if cardList[cardNumber][i][0] == "NOTE":
					numNote += 1
					value = numNote
				if cardList[cardNumber][i][0] == "UID":
					numUid += 1
					value = numUid
				if cardList[cardNumber][i][0] == "URL":
					numUrl += 1
					value = numUrl
				if cardList[cardNumber][i][0] == "OTHER":
					numOther += 1
					value = numOther

				query = "SELECT * FROM NAME where name = '%s'" % name
				cursor.execute(query)
				nameID = cursor.fetchone()[0]
				query = "INSERT INTO PROPERTY (name_id, pname, pinst, partype, parval, value) VALUES (%d, '%s', %d, '%s', '%s','%s');" % (nameID, cardList[cardNumber][i][0], value ,cardList[cardNumber][i][1], cardList[cardNumber][i][2], cardList[cardNumber][i][3])
				cursor.execute(query)
				cnx.commit()

def openFromDatabase():
	global cnx
	global cursor
	global saveDisabled

	tempCard = []
	tempCard2 = []

	query = "SELECT * FROM NAME;"
	cursor.execute(query)
	dataList = cursor.fetchall()
	if len(dataList) == 0:
		top = Toplevel()
		top.title("Error Opening")
		top.geometry('250x100+500+360')
		top.bind('<Escape>', lambda e: closeWindow(top))
		msg = Message(top, text = 'No Cards found in database', width = 200)
		msg.pack(expand = YES)
		button = Button(top, text = "Cancel", command = top.destroy)
		button.pack()
	else:
		if cardList != []:
			del cardList[:]
		root.title("Database")
		for i in dataList:
			name = i[1]
			tempCard = [('N', '', '', name)]
			query = "SELECT * FROM PROPERTY where name_id = '%s';" % i[0]
			cursor.execute(query)
			propList = cursor.fetchall()
			for j in propList:
				tempCard2 = (j[1],j[3],j[4],j[5])
				tempCard.append(tempCard2)
			cardList.append(tempCard)
		updateFileView()
		mlb.selection_set(0)
		updateCardView()
		saveDisabled = 1

def appendFromDatabase():
	global cnx
	global cursor
	global saveDisabled

	if len(cardList) != 0:
		query = "SELECT * FROM NAME;"
		cursor.execute(query)
		dataList = cursor.fetchall()
		if len(dataList) == 0:
			top = Toplevel()
			top.title("Error Appending")
			top.geometry('250x100+500+360')
			top.bind('<Escape>', lambda e: closeWindow(top))
			msg = Message(top, text = 'No Cards found in database', width = 200)
			msg.pack(expand = YES)
			button = Button(top, text = "Cancel", command = top.destroy)
			button.pack()
		else:
			for i in dataList:
				name = i[1]
				tempCard = [('N', '', '', name)]
				query = "SELECT * FROM PROPERTY where name_id = '%s';" % i[0]
				cursor.execute(query)
				propList = cursor.fetchall()
				for j in propList:
					tempCard2 = (j[1],j[3],j[4],j[5])
					tempCard.append(tempCard2)
				cardList.append(tempCard)
			updateFileView()
			mlb.selection_set(0)
			updateCardView()
			saveDisabled = 0

def query():
	global queryOpen
	global cnx
	global cursor

	def helpWindow():
		top = Toplevel()
		top.title("Help Window")
		top.geometry('400x100+500+360')
		top.bind('<Escape>', lambda e: closeWindow(top))
		Label(top, text = "Table NAME: name_id, name").pack(side = TOP, anchor = W)
		Label(top, text = "Table PROPERTY: name_id, pname, pinst, partype, parval, value").pack(side = TOP, anchor = W)
		Button(top, text = "Cancel", command = top.destroy).pack(side = BOTTOM)

	def clearResult():
		text2.delete(0.0, END)

	def insertResult(line):
		text2.insert(END, line)
		text2.yview(END)

	def submitButton():
		choice = v.get()
		if choice == 1:
			insertResult("Not IMPLEMENTED")
		if choice == 2:
			string = e2.get()
			query = "SELECT DISTINCT name_id FROM PROPERTY where pname = 'ADR' and value LIKE '%%;%%;%%;%%;%%;%s';" % string
			cursor.execute(query)
			results = cursor.fetchall()
			if len(results) == 0:
				insertResult("No Results Found\n------------------------------------------------------------")
			else:
				value = len(results)
				insertResult("There are: " + str(value) + " cards in " + string + "\n------------------------------------------------------------")
		if choice == 3:
			string = e3.get()
			query = "SELECT DISTINCT name_id FROM PROPERTY where pname = '%s';" % string
			cursor.execute(query)
			results = cursor.fetchall()
			if len(results) == 0:
				insertResult("No Results Found\n------------------------------------------------------------")
			else:
				value = len(results)
				insertResult("There are: " + str(value) + " cards that have the property " + string + "\n------------------------------------------------------------")
		if choice == 4:
			string = e4.get()
			query = "SELECT * FROM PROPERTY where pname = 'FN' and value LIKE '%s';" % string
			cursor.execute(query)
			results = cursor.fetchall()
			if len(results) == 0:
				insertResult("No Results Found\n------------------------------------------------------------")
			else:
				value = len(results)
				insertResult("There are: " + str(value) + " cards that have the name " + string + "\n------------------------------------------------------------")

	def queryClose():
		global queryOpen
		queryOpen = 0
		top.destroy()

	if queryOpen == 0:
	    queryOpen = 1
	    top = Toplevel()
	    top.title("Query Database...")
	    top.geometry('800x300+500+360')

	    #########QUERY PANEL###################
	    frame = Frame(top, relief = RAISED, bd = 2)
	    labelfont = ('bold', 10)
	    label = Label(frame, text = "Query", bg = 'grey', font = labelfont)
	    label.pack(anchor = W, fill = X)
	    v = IntVar()
	    Radiobutton(frame, variable = v, value = 1, text = "Display the properties of all cards with name ___ \n(SQL wild card % is permitted)").pack(anchor = W, side = TOP)
	    e1 = Entry(frame)
	    e1.pack(side = TOP, expand = YES, fill = X)
	    e1.insert(0, "SELECT")
	    Radiobutton(frame, variable = v, value = 2, text = "How many cards are in ____ (country)").pack(anchor = W, side = TOP)
	    e2 = Entry(frame)
	    e2.pack(side = TOP, expand = YES, fill = X)
	    e2.insert(0, "SELECT")
	    Radiobutton(frame, variable = v, value = 3, text = "How many cards have the _____ (property)").pack(anchor = W, side = TOP)
	    e3 = Entry(frame)
	    e3.pack(side = TOP, expand = YES, fill = X)
	    e3.insert(0, "SELECT")
	    Radiobutton(frame, variable = v, value = 4, text = "How many cards have the name ____ (full name)").pack(anchor = W, side = TOP)
	    e4 = Entry(frame)
	    e4.pack(side = TOP, expand = YES, fill = X)
	    e4.insert(0, "SELECT")
	    buttonFrame = Frame(frame)
	    Button(buttonFrame, text = "Submit", command = submitButton).pack(side = LEFT)
	    Button(buttonFrame, text = "Help", command = helpWindow).pack(side = LEFT)
	    buttonFrame.pack(side = BOTTOM)
	    frame.pack(side = LEFT, expand = YES, fill = BOTH)

	    #########RESULTS PANEL###################
	    frame2 = Frame(top, relief = RAISED, bd = 2)
	    label2 = Label(frame2, text = "Result", bg = 'grey', font = labelfont)
	    label2.pack(anchor = W, fill = X)
	    scroll = Scrollbar(frame2)
	    button = Button(frame2, text = "Clear", command = clearResult)
	    button.pack(side = BOTTOM)
	    text2 = Text(frame2, height = 15, width = 60, bg = 'white')
	    text2.configure(yscrollcommand = scroll.set)
	    text2.pack(side = LEFT, expand = YES)
	    scroll.pack(side = RIGHT, fill = Y)
	    frame2.pack(side = RIGHT, expand = YES, fill = BOTH)
	else:
	    return

	top.protocol('WM_DELETE_WINDOW', queryClose)

########### HELP MENU BUTTONS #####################
def aboutWindow():
	tkinter.messagebox.showinfo('XVCF', 'This is a Vcard reader\n\nCreated by: Michael Tran.'
		'\n\nThis application is only compatible with Vcard version 3.0')

def flagMeaning():
	top = Toplevel()
	top.title("About Flags and Colours")
	top.geometry('450x250+500+300')
	top.bind('<Escape>', lambda e: closeWindow(top))
	msg = Message(top, text = '\nFlag Meanings:\nC = card as a whole is in canonical form\n'
		'M = card has multiple same mandatory propeties: FN or N\n'
		'U, P, G = card has at least one URL, PHOTO or GEO property\n', width = 400)
	msg.pack()
	msg2 = Message(top, text = 'Colour Meanings:\nGreen = card is in canonical form (the C flag is on)\n'
		'Red = card needs fixing because (a) it has multiple mandatory properties (the M flag is on) or (b) its FN property has the same value as the preceding card\'s FN.\n'
		'Yellow  = default state if neither green nor red applies.\n', width = 370)
	msg2.pack()
	button = Button(top, text = "Cancel", command = top.destroy)
	button.pack()

########### Refresh File/Card Panel ###############
def updateFileView():
	global newCard
	global addProp
	firstCard = 0
	mlb.delete(0, END)
	if newCard == 0:
		clearCardView()
	for i in range(len(cardList)):
		adrCount = 0
		telCount = 0
		adrFlag = 0
		urlCount = 0
		nameCount = 0
		geoCount  = 0
		photoCount = 0
		name = ""
		region = ""
		country = ""
		flagString = ""
		uidFlag = 0
		fnFlag = 0
		
		for j in range(0, len(cardList[i])):
			propName = ""
			parVal = ""
			parType = ""
			value = ""
			if cardList[i][j][0] == "FN":
				if fnFlag == 0:
					name = cardList[i][j][3]
				fnFlag = 1
			if cardList[i][j][0] == "ADR":
				adrCount += 1
				if adrFlag == 0:
					address = cardList[i][j][3]
					splitAdr = address.split(';')
					if len(splitAdr) == 7:
						region = splitAdr[4]
						country = splitAdr[6]
				adrFlag = 1
			if cardList[i][j][0] == "TEL":
				telCount += 1
			if cardList[i][j][0] == "N":
				nameCount += 1
			if cardList[i][j][0] == "FN":
				nameCount += 1
			if cardList[i][j][0] == "URL":
				urlCount += 1
			if cardList[i][j][0] == "GEO":
				geoCount += 1
			if cardList[i][j][0] == "PHOTO":
				photoCount += 1
			if cardList[i][j][0] == "UID":
				uidString = cardList[i][j][3]
				uidFlag = 1

			#BUILDLING FLAG STRING
			if uidFlag == 1:
				uidCounter = 0
				uidFlag += 1
				if '@' in uidString:
					for c in uidString:
						if c == "@":
							uidCounter += 1
						if c == "*":
							flagString = "-"
							break
						if uidCounter == 2:
							flagString = "C"
							break
				else:
				    flagString = "?"
			else:
				flagString = "?"
			if nameCount > 2:
				flagString = flagString + "M"
			else:
				flagString = flagString + "-"
			if urlCount > 0:
				flagString = flagString + "U"
			else:
				flagString = flagString + "-"
			if photoCount > 0:
				flagString = flagString + "P"
			else:
				flagString = flagString + "-"
			if geoCount > 0:
				flagString = flagString + "G"
			else:
				flagString = flagString + "-"

		mlb.insert(END, ("%d" % (i+1), name, region, country, adrCount, telCount, flagString))
		firstCard = 1

def updateCardView():
	cardSelect = mlb.curselection()
	if len(cardSelect) > 0:
		clearCardView()
		cardNumber = int (cardSelect[0])
		for i in range(0, len(cardList[cardNumber])):
			propName = ""
			parVal = ""
			parType = ""
			value = ""
			propName = cardList[cardNumber][i][0]
			parType = cardList[cardNumber][i][1]
			if parType == None:
				parType = ""
			parVal = cardList[cardNumber][i][2]
			if parVal == None:
				parVal = ""
			value = cardList[cardNumber][i][3]
			mlb2.insert(END,(propName, parType, parVal, value))

def clearCardView():
	mlb2.delete(0, END)

########### MENU BAR ##############################
def mainWindowMenu(r):
	m = Menu(r)
	filemenu = Menu(m, tearoff = 0)
	filemenu.add("command", label = "Open..", command = openButton)
	filemenu.add("command", label = "Append..", command = appendButton)
	filemenu.add("command", label = "Save", command = saveButton)
	filemenu.add("command", label = "Save as..", command = saveAsButton)
	filemenu.add_separator()
	filemenu.add("command", label = "Exit", command = confirmQuit)

	editmenu = Menu(m, tearoff = 0)
	editmenu.add("command", label = "Sort", command = sortButton)
	editmenu.add("command", label = "Canonicalize", command = canonButton)
	editmenu.add("command", label = "Select", comman = selectButton)
	editmenu.add("command", label = "Undo", command = undoButton)

	datamenu = Menu(m, tearoff = 0)
	datamenu.add("command", label = "Store All", command = storeAll)
	datamenu.add("command", label = "Store Selected", command = storeSelected)
	datamenu.add("command", label = "Open from Database", command = openFromDatabase)
	datamenu.add("command", label = "Append from Database", command = appendFromDatabase)
	datamenu.add("command", label = "Query...", command = query)

	helpmenu = Menu(m, tearoff = 0)
	helpmenu.add("command", label = "Card flags and colours...", command = flagMeaning)
	helpmenu.add_separator()
	helpmenu.add("command", label= "About XVCF", command=aboutWindow)
	

	m.add("cascade", menu = filemenu, label = "File")
	m.add("cascade", menu = editmenu, label = "Organize")
	m.add("cascade", menu = datamenu, label = "Database")
	m.add("cascade", menu = helpmenu, label = "Help")

	return m

########### Main Window ###########################
def buildMainWindow():
	global cnx
	global cursor

	if(len(sys.argv) != 3):
		print("Please give username and password\nUsage python3 xvcf.py [username][password]")
		sys.exit()
	else:
		try:
			cnx = mysql.connector.connect(user=sys.argv[1], password= sys.argv[2], host='dursley.socs.uoguelph.ca', database=sys.argv[1])		
			cursor = cnx.cursor()
			query = "CREATE TABLE IF NOT EXISTS NAME (name_id SERIAL PRIMARY KEY AUTO_INCREMENT, name VARCHAR(60) NOT NULL);"
			cursor.execute(query)
			query = "CREATE TABLE IF NOT EXISTS PROPERTY (PRIMARY KEY (name_id, pname, pinst), FOREIGN KEY (name_id) REFERENCES NAME (name_id) ON DELETE CASCADE, name_id INT NOT NULL, pname CHAR(8) NOT NULL, pinst SMALLINT NOT NULL, partype TINYTEXT, parval TINYTEXT, value TEXT);"
			cursor.execute(query)
		except mysql.connector.Error as err:
			if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
				print("Something is wrong with your user name or password\nUsage python3 xvcf.py [username][password]")
				sys.exit()
			elif err.errno == errorcode.ER_BAD_DB_ERROR:
				print("Database does not exists\nUsage python3 xvcf.py [username][password]")
				sys.exit()
			else:
			    print(err)
			    sys.exit()

	root.title("XVCF")
	root.minsize(1000,600)
	root.configure(bg = "grey")

	m = mainWindowMenu(root)
	root.configure(menu = m)

	#GUI PANELS
	fileDisplay()
	mlb.pack(expand = YES, fill = BOTH)
	fileButtons()
	frame = Frame(height = 2, bd = 1, relief = SUNKEN)
	frame.pack(fill = X, pady = 5)
	card_Display()
	mlb2.pack(expand = YES, fill = BOTH)
	cardButtons()
	frame2 = Frame(height = 2, bd = 1, relief = SUNKEN)
	frame2.pack(fill = X, pady = 5)	
	logDisplay()
	startWebServer(44704)

mw = buildMainWindow()
root.protocol('WM_DELETE_WINDOW', confirmQuit)
root.mainloop()