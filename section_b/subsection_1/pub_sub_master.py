class Master:
    def __init__(self):
        self.subscribers = list()
        self.publishers = list()

    def add_subscriber(self, topic, cbk):
        sub = Subcriber()
        sub.set_topic(topic)
        sub.set_callback(cbk)
        self.subscribers.append(sub)
        return sub

    def add_publisher(self, topic):
        pub = Publisher()
        pub.set_master(self)
        pub.set_topic(topic)
        self.publishers.append(pub)
        return pub

    def _published(self, topic, data):
        for sub in self.subscribers:
            if sub.topic == topic:
                sub.callback(data)


class Subcriber:
    def __init__(self):
        self.topic = ""
        self.callback = None

    def set_topic(self, topic):
        self.topic = topic

    def set_callback(self, cbk):
        self.callback = cbk


class Publisher:
    def __init__(self):
        self.topic = ""
        self.mstr = None

    def set_topic(self, topic):
        self.topic = topic

    def set_master(self, mstr):
        self.mstr = mstr

    def publish(self, data):
        self.mstr._published(self.topic, data)


################################################################################################

def my_callback(data):
    print("This is from callback")
    print("DATA :", data)


if __name__ == "__main__":
    my_master = Master()

    sub1 = my_master.add_subscriber("/hello", my_callback)

    pub1 = my_master.add_publisher("/hello")

    pub1.publish("THis is my first message")
