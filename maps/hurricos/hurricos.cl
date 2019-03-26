_CORIUM_SCRIPT;

_BEGIN;
	_PRINT "Running map scripts...";
	
	_LOAD_SETTINGS "maps/hurricos/hurricos.cfg";
	
	_LOOP 135;
		_PRINT "loading chunk %";
		
		_MAP; # map commands
			_OBJECT "gfx/hurricoschunks/hurricos.%.obj" NULL "gfx/Hurricos.png"
				(0.0f, 0.0f, 0.0f) (0.0f, 0.0f, 0.0f) (15.0f, 15.0f, 15.0f) true true;
		_ENDMAP;
	_ENDLOOP;
_END;
