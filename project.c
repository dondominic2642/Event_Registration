
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Scanner;

public class EventRegistrationSystem {

public static void main(String[] args) {  
    Scanner scanner = new Scanner(System.in);  
    Organizer organizer = new Organizer();  
    System.out.println("--- Welcome to the Event Registration System ---");  
    System.out.println("Today's Date: " + LocalDate.now());  

    while (true) {  
        displayMenu();  
        System.out.print("Enter your choice: ");  
        String choiceStr = scanner.nextLine();  
        int choice;  

        try {  
            choice = Integer.parseInt(choiceStr);  
        } catch (NumberFormatException e) {  
            System.out.println("Invalid input. Please enter a number.");  
            continue;  
        }  

        switch (choice) {  
            case 1:  
                handleCreateEvent(scanner, organizer);  
                break;  
            case 2:  
                handleAddParticipant(scanner, organizer);  
                break;  
            case 3:  
                handleRegisterParticipant(scanner, organizer);  
                break;  
            case 4:  
                handleCancelRegistration(scanner, organizer);  
                break;  
            case 5:  
                handleDisplayParticipants(scanner, organizer);  
                break;  
            case 6:  
                System.out.println("Thank you for using the system. Goodbye!");  
                scanner.close();  
                return;  
            default:  
                System.out.println(" Invalid choice. Please select a valid option from the menu.");  
        }  
        System.out.println("\nPress Enter to continue...");  
        scanner.nextLine();  
    }  
}  

private static void displayMenu() {  
    System.out.println("\n==========================================");  
    System.out.println(" MENU ");  
    System.out.println("==========================================");  
    System.out.println("1. Create a new Event");  
    System.out.println("2. Add a new Participant");  
    System.out.println("3. Register a Participant for an Event");  
    System.out.println("4. Cancel a Registration");  
    System.out.println("5. Display Participant List for an Event");  
    System.out.println("6. Exit");  
    System.out.println("==========================================");  
}  

private static void handleCreateEvent(Scanner scanner, Organizer organizer) {  
    System.out.println("\n--- Create New Event ---");  
    System.out.print("Enter Event Name: ");  
    String name = scanner.nextLine();  

    LocalDate date = null;  
    while (date == null) {  
        System.out.print("Enter Event Date (YYYY-MM-DD): ");  
        String dateStr = scanner.nextLine();  
        try {  
            date = LocalDate.parse(dateStr);  
        } catch (DateTimeParseException e) {  
            System.out.println("Invalid date format. Please use YYYY-MM-DD.");  
        }  
    }  

    System.out.print("Enter Event Location: ");  
    String location = scanner.nextLine();  
     
    int capacity = 0;  
    while (capacity <= 0) {  
        System.out.print("Enter Maximum Capacity: ");  
        String capacityStr = scanner.nextLine();  
        try {  
            capacity = Integer.parseInt(capacityStr);  
            if (capacity <= 0) {  
                System.out.println("Capacity must be a positive number.");  
            }  
        } catch (NumberFormatException e) {  
            System.out.println("Invalid input. Please enter a valid number for capacity.");  
        }  
    }  
     
    organizer.createEvent(name, date, location, capacity);  
}  

private static void handleAddParticipant(Scanner scanner, Organizer organizer) {  
    System.out.println("\n--- Add New Participant ---");  
    System.out.print("Enter Participant ID (e.g., P101): ");  
    String id = scanner.nextLine();  
    System.out.print("Enter Participant Name: ");  
    String name = scanner.nextLine();  
    System.out.print("Enter Participant Contact Info (Email/Phone): ");  
    String contact = scanner.nextLine();  
     
    Participant participant = new Participant(id, name, contact);  
    organizer.addParticipant(participant);  
    System.out.println("Participant added successfully!");  
}  
 
private static void handleRegisterParticipant(Scanner scanner, Organizer organizer) {  
    System.out.println("\n--- Register Participant for an Event ---");  
    System.out.print("Enter Participant ID to register: ");  
    String participantId = scanner.nextLine();  
    System.out.print("Enter the Name of the Event: ");  
    String eventName = scanner.nextLine();  
     
    organizer.registerParticipantForEvent(participantId, eventName);  
}  

private static void handleCancelRegistration(Scanner scanner, Organizer organizer) {  
    System.out.println("\n--- Cancel a Registration ---");  
    System.out.print("Enter Participant ID to cancel registration for: ");  
    String participantId = scanner.nextLine();  
    System.out.print("Enter the Name of the Event: ");  
    String eventName = scanner.nextLine();  
     
    organizer.cancelRegistration(participantId, eventName);  
}  

private static void handleDisplayParticipants(Scanner scanner, Organizer organizer) {  
    System.out.println("\n--- Display Participant List ---");  
    System.out.print("Enter the Name of the Event: ");  
    String eventName = scanner.nextLine();  
     
    organizer.displayParticipantList(eventName);  
}

}

class Participant {
private final String id;
private String name;
private String contactInformation;

public Participant(String id, String name, String contactInformation) {  
    this.id = id;  
    this.name = name;  
    this.contactInformation = contactInformation;  
}  

public String getId() { return id; }  
public String getName() { return name; }  
 
@Override  
public String toString() {  
    return "Participant[ID=" + id + ", Name=" + name + ", Contact=" + contactInformation + "]";  
}

}

class Event {
private final String name;
private final LocalDate date;
private final String location;
private final int maximumCapacity;
private final List<Registration> registrations;

public Event(String name, LocalDate date, String location, int maximumCapacity) {  
    this.name = name;  
    this.date = date;  
    this.location = location;  
    this.maximumCapacity = maximumCapacity;  
    this.registrations = new ArrayList<>();  
}  

public String getName() { return name; }  
public int getMaximumCapacity() { return maximumCapacity; }  
public List<Registration> getRegistrations() { return registrations; }  
public boolean isFull() { return registrations.size() >= maximumCapacity; }  

public boolean addRegistration(Registration registration) {  
    if (!isFull()) {  
        registrations.add(registration);  
        return true;  
    }  
    return false;  
}  

public void removeRegistration(Registration registration) {  
    registrations.remove(registration);  
}

}

class Registration {
private final Participant participant;
private final Event event;
private final LocalDateTime registrationTime;

public Registration(Participant participant, Event event) {  
    this.participant = participant;  
    this.event = event;  
    this.registrationTime = LocalDateTime.now();  
}  

public Participant getParticipant() { return participant; }

}

class Organizer {
private final List<Event> events;
private final List<Participant> participants;

public Organizer() {  
    this.events = new ArrayList<>();  
    this.participants = new ArrayList<>();  
}  

public void createEvent(String name, LocalDate date, String location, int capacity) {  
    Event newEvent = new Event(name, date, location, capacity);  
    events.add(newEvent);  
    System.out.println("Event created successfully: " + name);  
}  

public void addParticipant(Participant participant) {  
    participants.add(participant);  
}  

private Optional<Event> findEventByName(String name) {  
    return events.stream().filter(e -> e.getName().equalsIgnoreCase(name)).findFirst();  
}  

private Optional<Participant> findParticipantById(String id) {  
    return participants.stream().filter(p -> p.getId().equalsIgnoreCase(id)).findFirst();  
}  

public void registerParticipantForEvent(String participantId, String eventName) {  
    Optional<Event> eventOpt = findEventByName(eventName);  
    Optional<Participant> participantOpt = findParticipantById(participantId);  

    if (eventOpt.isPresent() && participantOpt.isPresent()) {  
        Event event = eventOpt.get();  
        Participant participant = participantOpt.get();  

        if (event.isFull()) {  
            System.out.println("Registration failed for " + participant.getName() + ". Event '" + event.getName() + "' is full.");  
            return;  
        }  
         
        boolean alreadyRegistered = event.getRegistrations().stream()  
            .anyMatch(reg -> reg.getParticipant().getId().equals(participantId));  

        if (alreadyRegistered) {  
             System.out.println("" + participant.getName() + " is already registered for '" + event.getName() + "'.");  
             return;  
        }  

        Registration newRegistration = new Registration(participant, event);  
        if (event.addRegistration(newRegistration)) {  
            System.out.println("Successfully registered " + participant.getName() + " for '" + event.getName() + "'.");  
        }  
    } else {  
        if (!eventOpt.isPresent()) System.out.println("Registration failed. Event '" + eventName + "' not found.");  
        if (!participantOpt.isPresent()) System.out.println(" Registration failed. Participant with ID '" + participantId + "' not found.");  
    }  
}  

public void cancelRegistration(String participantId, String eventName) {  
    Optional<Event> eventOpt = findEventByName(eventName);  
    if (eventOpt.isPresent()) {  
        Event event = eventOpt.get();  
        Optional<Registration> registrationOpt = event.getRegistrations().stream()  
                .filter(reg -> reg.getParticipant().getId().equals(participantId))  
                .findFirst();  

        if (registrationOpt.isPresent()) {  
            Registration registration = registrationOpt.get();  
            event.removeRegistration(registration);  
            System.out.println(" Successfully canceled registration for " + registration.getParticipant().getName() + " from '" + event.getName() + "'.");  
        } else {  
            System.out.println(" Cancellation failed. Participant with ID " + participantId + " not found in event '" + eventName + "'.");  
        }  
    } else {  
        System.out.println(" Cancellation failed. Event '" + eventName + "' not found.");  
    }  
}  

public void displayParticipantList(String eventName) {  
    Optional<Event> eventOpt = findEventByName(eventName);  
    if (eventOpt.isPresent()) {  
        Event event = eventOpt.get();  
        System.out.println("\n--- Participant List for: " + event.getName() + " ---");  
        System.out.println("Capacity: " + event.getRegistrations().size() + "/" + event.getMaximumCapacity());  
         
        if (event.getRegistrations().isEmpty()) {  
            System.out.println("No participants registered yet.");  
        } else {  
            event.getRegistrations().forEach(reg -> System.out.println(" -> " + reg.getParticipant()));  
        }  
        System.out.println("-------------------------------------------------");  
    } else {  
        System.out.println(" Event '" + eventName + "' not found.");  
    }  
}

}


