def IMPORT(url, server)
 @url = url
 @server = server
end
def startServer(intload)
 @intload = intload
end
SERVER = [IMPORT("http://190.0.0.1:5080")]
module listen
 port = 5080
 if SERVER = true
  servers = http.request(SERVER)
  Net::HTTP.start(SERVER.hostname, SERVER.port) do |http|
   servers;
 end
end

listen.SERVER;

uri = SERVER.sample
req = Net::HTTP::Post.new(uri)
req.set_form_data('from' => '2005-01-01', 'to' => '2005-03-31')

res = Net::HTTP.start(uri.hostname, uri.port) do |http|
  http.request(req)
end

case res
when Net::HTTPSuccess, Net::HTTPRedirection
  # OK
else
  res.value
end
