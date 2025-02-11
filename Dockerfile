FROM agulinari/appserverbase:v1
COPY AppServer /AppServer
COPY log4cpp.properties /
RUN cd /AppServer/cmake && cmake . && make
EXPOSE 3000
CMD ["./AppServer/cmake/AppServer", "-p", "3000", "-s", "http://shared-server-match.herokuapp.com"]
