# -*- coding: utf-8 -*-
"""animal_shelter.py

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1ZTs5kMGmJC4KjBg3lXBrk2ENxOxlRdjx
"""

#This require sign in on the proper database with the correct username and password within the terminal
#Username and password is now stored in environment variable and can access them within the applicaiton

from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
   """ CRUD operations for Animal Collection in MongoDB """
   def __init__(self, user, pwd):
        #Initialize MongoClient to help access
        #MongoDB databases and collections
        #nv.desktop-services.apporto.com:

        #Connection Variables
        USER = 'MONGO_USERNAME'
        PASS = 'MONGO_PASSWORD'
        HOST = 'nv-desktop-services.apporto.com'
        PORT = 32222
        DB = 'AAC'
        COL = 'animals'

        self.client = MongoClient('mongodb://%s:%s@nv-desktop-services.apporto.com:32222' % (user, pwd))

        self.database = self.client['AAC'] #AAC is the name of the database that is being accessed
        print('Hello Animal Shelter')

#Creates new entry into the database
   def create(self, data):
        print("Working in Create Method...")
        if data is not None:
            insertSuccess = self.database.animals.insert(data) #Data should be within dictionary
            if insertSuccess != 0:
                return False
            #Default Return
            return True
        else:
            raise Exception("There is nothing to save!") #There is an error for an empty parameter


#Read database and return any entries that match inquired search terms
   def read(self, searchData):
        print("Working in Read Method...")
        if searchData:
            data = self.database.animals.find(searchData, {"_id": False})
        else:
            data = self.database.animals.find({}, {"_id": False})
        return data


#Update any entries after skimming through database and finding a match
   def update(self, searchData, updateData):
        print("Working in Update Method...")

        if searchData is not None:
            result = self.database.animals.update_many(searchData, {"$set": updateData})
        else:
            return "{}"
        return result.raw_result


#Delete entries that do match the search results from the database
   def delete(self, deleteData):
        print("Working in Delete Method...")
        if deleteData is not None:
            result = self.database.animals.delete_many(deleteData)
        else:
            return "{}"
        return result.raw_result