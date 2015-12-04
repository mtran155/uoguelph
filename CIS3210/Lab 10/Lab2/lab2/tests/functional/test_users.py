from lab2.tests import *

class TestUsersController(TestController):

   # def test_index(self):
    #    response = self.app.get(url(controller='users', action='index'))
      #  assert 'Home' in response
        
    def test_get(self):
	response = self.app.get(url(controller='users', action='userid'))
	assert "Getting " in response
	
    def test_put(self):
	response = self.app.put(url(controller='users', action='userid'))
	assert "Updating " in response

    def test_post(self):
	response = self.app.post(url(controller='users', action='userid'))
	assert "Creating " in response
	
    def test_delete(self):
	response = self.app.delete(url(controller='users', action='userid'))
	assert "Deleting " in response